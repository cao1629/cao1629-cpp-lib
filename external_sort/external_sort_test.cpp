#include <gtest/gtest.h>
#include "external_sort.h"


namespace cao1629 {

TEST(ExternalSortTest, TestFirstRound) {
  ExternalSort external_sort;
  external_sort.CreateNumbersFile("source.data", 100000000);
  external_sort.FirstRound();
  EXPECT_EQ(external_sort.files_[1], 1000);

  for (int i = 1; i <= 100; i++) {
    std::string filename = external_sort.LogName(1, i);
    std::filesystem::remove(filename);
  }
}


TEST(ExternalSort, TestEndOfPageFlag) {
  {
    std::ofstream out("output.txt");
    char buffer[4];
    Serialize(1, buffer);
    out.write(buffer,4);

    out.write(END_OF_PAGE_FLAG, 4);
  }

  {
    std::ifstream in("output.txt");
    char buffer[4];
    in.read(buffer, 4);
    int val = Deserialize(buffer);
    EXPECT_EQ(val, 1);

    in.read(buffer, 4);
    val = Deserialize(buffer);
    EXPECT_EQ(val, -1);
  }
  std::filesystem::remove("output,.txt");
}


TEST(ExternalSort, TestFileReader) {
  std::string filename = "numbers.data";
  ExternalSort external_sort;
  external_sort.CreateNumbersFile(filename, 15000);
  int read_numbers = 0;
  FileReader file_reader(filename, external_sort.buffer_pool_[0]);

  while (file_reader.Next() >= 0) {
    read_numbers++;
  }

  EXPECT_EQ(read_numbers, 15000);
  std::filesystem::remove(filename);
}

TEST(ExternalSort, TestFileWriter) {
  std::string filename = "output.data";
  {
    std::shared_ptr<ExternalSort::Page> page = std::make_shared<ExternalSort::Page>();
    FileWriter file_writer("output.data", page);
    for (int i = 1; i <= 15000; i++) {
      file_writer.WriteInt(i);
    }
    file_writer.Finish();
  }

  {
    std::shared_ptr<ExternalSort::Page> page = std::make_shared<ExternalSort::Page>();
    FileReader file_reader(filename, page);
    int num_numbers = 0;
    while (file_reader.Next() > 0) {
      num_numbers++;
    }

    EXPECT_EQ(15000, num_numbers);
  }

  std::filesystem::remove("output.data");
}

TEST(ExternalSortTest, TestSort) {
  ExternalSort external_sort;
  external_sort.CreateNumbersFile("source.data", 100000000);
  external_sort.Sort();
}


}