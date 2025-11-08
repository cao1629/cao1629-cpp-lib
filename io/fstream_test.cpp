#include <gtest/gtest.h>
#include <fstream>
#include <filesystem>

namespace cao1629 {

TEST(fstreamTest, WriteHelloWorld) {
  const std::string filename = "test_hello.txt";

  // Create and write to file
  {
    std::ofstream file(filename);
    ASSERT_TRUE(file.is_open());
    file << "Hello, world!";
  } // RAII, close the file

  // Verify the file was created and contains the correct content
  {
    std::ifstream file(filename);
    ASSERT_TRUE(file.is_open());

    std::string content;
    std::getline(file, content);
    EXPECT_EQ(content, "Hello, world!");
  }

  // Clean up
  std::filesystem::remove(filename);
}


TEST(fstreamTest, TestAppendNumbers) {
  const std::string filename = "numbers.txt";
  std::ofstream file(filename);

  // We will use formatted writes down below.
  // 1 byte, 1 byte, 1 byte, 4 byte
  std::vector<int> nums{1, 2, 3, 1000000001};
  for (int v : nums) {
    file << v << " ";
  }
  file.close();
}


TEST(fstreamTest, TestSeek) {
  const std::string filename = "seek.txt";

  // Write "AAAAAAAAAA" to the file
  {
    std::ofstream file(filename);
    ASSERT_TRUE(file.is_open());
    file << "AAAAAAAAAA";
  }

  // Seek to the middle and write "B"
  {
    std::fstream file(filename);
    ASSERT_TRUE(file.is_open());
    file.seekp(5);  // Seek to position 5 (middle of 10 characters)
    file << "B";
  }

  // Verify the result is "AAAAABAAAA"
  {
    std::ifstream file(filename);
    ASSERT_TRUE(file.is_open());
    std::string content;
    std::getline(file, content);
    EXPECT_EQ(content, "AAAAABAAAA");
  }

  // Clean up
  // std::filesystem::remove(filename);
}

TEST(fstreamTest, TestEOF) {
  const std::string filename = "nums.txt";
  // Write integers to the file
  {
    std::ofstream file(filename);
    std::vector<int> nums{1, 2, 3, 4, 5};
    for (int v : nums) {
      file << v;
    }
  }

  {
    std::ifstream file(filename, std::ios::in);
    char buffer[40];
    file.read(buffer, 5);
    // eof() is false.
    // Even though now we've reached, we need another failed read.
    EXPECT_EQ(file.eof(), false);

    file.read(buffer+5, 1);
    EXPECT_EQ(file.eof(), true);
  }
  std::filesystem::remove(filename);
}


TEST(fstreamTest, TestReadIntegers) {
  const std::string filename = "integers.txt";

  // Write integers to the file
  // Each integer takes one byte on the file and separated by space.
  {
    std::ofstream file(filename);
    std::vector<int> nums{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    for (int v : nums) {
      // 31, 32, 33, 34 ...
      // ASCII code of 1, 2, 3, 4, 5
      file << v << " ";
    }
  }

  // Read integers from the file
  {
    std::ifstream file(filename);
    std::vector<int> nums;
    int v;

    // drain the file with formatted reads
    //
    while (file >> v) {
      nums.push_back(v);
    }
    std::vector<int> expected{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    EXPECT_EQ(nums, expected);
  }

}

TEST(fstreamTest, TestReadIntegers2) {
  const std::string filename = "integers.txt";

  // Write integers to the file
  // Each integer takes one byte.
  {
    std::ofstream file(filename);
    std::vector<int> nums{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    for (int v : nums) {
      char c = v;
      file << c;
    }
  }

  {
    std::ifstream in(filename, std::ios::in);
    std::vector<int> nums;
    std::uint8_t buffer;

    // do not write:
    // while (!in.eof()) {
    //
    // }
    while (in.read(reinterpret_cast<char*>(&buffer), 1) || in.gcount() > 0) {
      // uint8_t -> int
      nums.push_back(buffer);
    }

    std::vector<int> expected{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    EXPECT_EQ(nums, expected);
  }
}


TEST(fstreamTest, TestGetMethod) {
  const std::string filename = "integers.txt";

  {
    std::ofstream file(filename);
    std::vector<int> nums{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    for (int v : nums) {
      char c = v;

      // 01, 02, 03, 04 .....
      file << c;
    }
  }

  {
    std::ifstream in(filename);
    in.seekg(5);
    int c = in.get();
    EXPECT_EQ(c, 6);
  }

  {
    std::ifstream in(filename);
    std::vector<int> nums;
    char c;
    while (in.get(c)) {
      nums.push_back(c);
    }
    std::vector<int> expected{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    EXPECT_EQ(nums, expected);
  }
}


TEST(fstreamTest,TestPut) {
  const std::string filename = "output.txt";
  std::ofstream out(filename);

  // return ostream&
  out.put(1);    // 0000 0001
  out.put('A');  // 65: 0100 0001
  out.put(0xFF);  // 0xFF is int
  out.close();
}

TEST(fstreamTest, TestPut1) {

}


TEST(fstreamTest, Test2) {
  char buffer[4] = {1, 0, 0, 0};
  std::ofstream out("output.log");
  out.write(buffer, 4);
}

TEST(fstreamTest, TestPartialRead) {
  {
    std::ofstream out("output.txt");
    out << 1 << 2 << 3 << 4;
  }

  {
    std::ifstream in("output.txt");
    char buffer[10];
    in.read(buffer, 10);
    EXPECT_EQ(true, in.eof());
  }
}

}