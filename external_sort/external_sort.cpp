#include "external_sort.h"
#include <fstream>
#include <queue>

namespace cao1629 {
void Serialize(int val, char* buffer) {
  memcpy(buffer, &val, 4);
}

// encounter end-of-page flag 0xFFFFFFFF, return -1
int Deserialize(const char* buffer) {
  char end_of_data[4] = {-1, -1, -1, -1};
  if (memcmp(buffer, end_of_data, 4) == 0) {
    return -1;
  }
  int val;
  memcpy(&val, buffer, 4);
  return val;
}

void ExternalSort::CreateNumbersFile(std::string filename, size_t num_numbers) {
  filename_ = std::move(filename);
  std::ofstream out(filename_, std::ios::out | std::ios::app);
  size_t file_offset = 0;

  char buffer[4];
  for (int i = 1; i <= num_numbers; i++) {
    Serialize(i, buffer);
    out.write(buffer, 4);
    file_offset += 4;
  }

  if (file_offset % PAGE_SIZE != 0) {
    out.write(END_OF_PAGE_FLAG, 4);
  }
  out.flush();
}


void ExternalSort::FirstRound() {
  int page_number = 1;
  std::ifstream in(filename_);
  std::vector<int> nums_fit_in_memory;
  char page[PAGE_SIZE];

  int slot = 0;
  for (;;) {
    // read a page into the slot
    in.read(page, PAGE_SIZE);

    if (in.eof()) {
      // if slot == 0, we just write out a file. We don't have to create a new file
      // with no content.
      // if slot > 1, we do have content we need to write out to disk.
      if (slot > 0) {
        // Write out this file
        std::string log = LogName(1, page_number);
        PersistSortedNumbers(log, nums_fit_in_memory);
        nums_fit_in_memory.clear();
      }
      files_[1] = page_number - 1;
      return;
    }

    auto read = in.gcount();

    if (read < PAGE_SIZE) {
      // eof flag that can be detected by deserializer
      auto* p = reinterpret_cast<uint32_t*>(page + read);
      *p = 0xFFFFFFF;
      memset(page + read + 1, 0, PAGE_SIZE - read - 1);

      // Read all number from this page
      ReadNumbersFromPage(nums_fit_in_memory, page);

      // write out
      std::string log = LogName(1, page_number);
      PersistSortedNumbers(log, nums_fit_in_memory);
      nums_fit_in_memory.clear();
      files_[1] = page_number - 1;
      return;
    }

    // Read all numbers from this page
    ReadNumbersFromPage(nums_fit_in_memory, page);

    slot = (slot + 1) % 10;

    if (slot == 0) {
      // write out
      std::string log = LogName(1, page_number);
      page_number++;
      PersistSortedNumbers(log, nums_fit_in_memory);
      nums_fit_in_memory.clear();
    }
  }
}


void ExternalSort::PersistSortedNumbers(std::string filename, std::vector<int>& unsorted_numbers) {
  std::sort(unsorted_numbers.begin(), unsorted_numbers.end());
  std::ofstream out(filename, std::ios::out | std::ios::app);

  char buffer[4];
  for (int v : unsorted_numbers) {
    Serialize(v, buffer);
    out.write(buffer, 4);
  }
  out.flush();
}


void ExternalSort::ReadNumbersFromPage(std::vector<int>& numbers, char* page) {
  size_t offset = 0;
  while (offset < PAGE_SIZE) {
    int val = Deserialize(page + offset);
    if (val < 0) {
      break;
    }
    numbers.push_back(val);
    offset += 4;
  }
}

void ExternalSort::MergeFiles(int round, int start, int end, int file_number) {
  std::vector<std::shared_ptr<FileReader>> readers;

  for (int i = start; i <= end; i++) {
    std::string input = LogName(round, start);
    readers.push_back(std::make_shared<FileReader>(input, buffer_pool_[i - start]));
  }

  std::string output = LogName(round + 1, file_number);
  FileWriter file_writer(output, buffer_pool_.back());


  struct Compare {
    bool operator()(const std::pair<int, int>& a, const std::pair<int, int>& b) const {
      return a.second > b.second;
    }
  };

  std::priority_queue<std::pair<int, int>,
                      std::vector<std::pair<int, int>>, Compare> pq;

  // Initialize the min heap
  int n = end - start + 1;
  for (int i = 0; i < n; i++) {
    int val = readers[i]->Next();
    if (val < 0) {
      readers[i].reset();
      continue;
    }
    pq.push({i, val});
  }

  while (!pq.empty()) {
    auto e = pq.top();
    pq.pop();
    file_writer.WriteInt(e.second);
    if (readers[e.first]) {
      int val = readers[e.first]->Next();

      if (val < 0) {
        readers[e.first].reset();
      } else {
        pq.emplace(e.first, val);
      }
    }
  }

  // we're done merging. Files from the previous round are not needed any more.
  for (int i = start; i <= end; i++) {
    std::string filename = LogName(round, start);
    std::filesystem::remove(filename);
  }
}


void ExternalSort::MergeCurrentRound(int round) {
  int num_files = files_[round];
  int file_number = 1;
  int start = 1;
  while (start+NUM_PAGES-1 <= num_files) {
    int end = start+NUM_PAGES-1;
    MergeFiles(round, start, end, file_number);
    file_number++;
    start = end+1;
  }

  if (start < num_files) {
    MergeFiles(round, start, num_files, file_number);
    file_number++;
  }
  files_[round+1] = file_number-1;
}

void ExternalSort::Sort() {
  FirstRound();
  int cur_round = 1;
  do {
    MergeCurrentRound(1);
    cur_round++;
  } while (files_[cur_round] == 1);
}


FileReader::FileReader(std::string filename, std::shared_ptr<ExternalSort::Page> page) :
  filename_(std::move(filename)), page_(page) {
  in_.open(filename_);

  // Load the first page to buffer page
  in_.read(page_->data_, PAGE_SIZE);

  // -1 we have more than one page
  // -2 we only have one page, and this page is full
  // -3 we only have one page, and this page is not full. An end-of-page flag 0xFF FF FF FF indicates the end.

  auto read = in_.gcount();
  if (read < PAGE_SIZE) {
    file_offset_ = read;
  }
  else {
    file_offset_ = PAGE_SIZE;
  }

  page_offset_ = 0;
}


int FileReader::Next() {
  if (end_) {
    return -1;
  }

  int val = Deserialize(page_->data_ + page_offset_);
  page_offset_ += 4;

  // reach the end-of-file
  if (val < 0) {
    end_ = true;
    return -1;
  }

  // we just read a full page. Now we need to the next page.
  if (page_offset_ == PAGE_SIZE) {
    // first try to read the next page, then we could have 2 cases:
    // -1 next page exists
    // -2 eof
    in_.seekg(file_offset_);
    in_.read(page_->data_, PAGE_SIZE);

    auto read = in_.gcount();

    if (read == 0) {
      end_ = true;
    }

    file_offset_ += read;
    page_offset_ = 0;
  }

  return val;
}

FileWriter::FileWriter(std::string filename, std::shared_ptr<ExternalSort::Page> page) :
  filename_(std::move(filename)), page_(page) {
  out_.open(filename_, std::ios::out | std::ios::app);
  page_offset_ = 0;
}

void FileWriter::WriteInt(int val) {
  Serialize(val, buffer);
  memcpy(page_->data_ + page_offset_, buffer, 4);
  page_offset_ += 4;

  if (page_offset_ == PAGE_SIZE) {
    Flush();
    page_offset_ = 0;
  }
}

// Flush the current page to disk
void FileWriter::Flush() {
  out_.write(page_->data_, page_offset_);
  out_.flush();
}


void FileWriter::Finish() {
  if (page_offset_ > 0) {
    Flush();
    WriteEndOfPageFlag();
  }
}


void FileWriter::WriteEndOfPageFlag() {
  out_.write(END_OF_PAGE_FLAG, 4);
  page_offset_ += 4;
  if (page_offset_ == PAGE_SIZE) {
    page_offset_ = 0;
  }
}
}
