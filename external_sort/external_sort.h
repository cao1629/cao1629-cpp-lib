#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include <memory>
#include <fstream>

namespace cao1629 {

static const size_t PAGE_SIZE = 40000;
static const size_t NUM_PAGES = 10;
static const char END_OF_PAGE_FLAG[4]{-1, -1, -1, -1};

void Serialize(int val, char* buffer);

int Deserialize(const char* buffer);


class ExternalSort {
public:

  ExternalSort() {
    for (int i = 0; i < NUM_PAGES; i++) {
      buffer_pool_.push_back(std::make_shared<Page>());
    }
  }

  void CreateNumbersFile(std::string filename, size_t num_numbers);

  void FirstRound();

  // merge files from round[start, end]
  void MergeFiles(int round, int start, int end, int file_number);

  void PersistSortedNumbers(std::string filename, std::vector<int> &unsorted_numbers);

  std::string LogName(int round, int log_number) {
    return std::to_string(round) + '_' + std::to_string(log_number) + ".log";
  }

  void ReadNumbersFromPage(std::vector<int> &numbers, char *page);

  void Sort();

  void MergeCurrentRound(int round);


  std::string filename_;
  // found -> how many files generated in this round
  std::unordered_map<int, int> files_;

  struct Page {
    char data_[PAGE_SIZE];
  };

  std::vector<std::shared_ptr<Page>> buffer_pool_;
};


class FileReader {
public:

  FileReader(std::string filename, std::shared_ptr<ExternalSort::Page> page);


  int Next();

  std::shared_ptr<ExternalSort::Page> page_;
  size_t page_offset_;
  size_t file_offset_;
  std::string filename_;
  std::ifstream in_;
  bool end_{false};
};


class FileWriter {
public:

  FileWriter(std::string filename, std::shared_ptr<ExternalSort::Page> page);

  void WriteInt(int val);

  void WriteEndOfPageFlag();

  void Flush();

  void Finish();

  std::ofstream out_;
  std::string filename_;
  size_t page_offset_;
  std::shared_ptr<ExternalSort::Page> page_;
  char buffer[4];
};

};