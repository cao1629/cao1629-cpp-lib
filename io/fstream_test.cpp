#include <gtest/gtest.h>
#include <fstream>
#include <filesystem>

namespace cao1629 {

TEST(FileTest, WriteHelloWorld) {
  const std::string filename = "test_hello.txt";

  // Create and write to file
  {
    std::ofstream file(filename);
    ASSERT_TRUE(file.is_open());
    file << "Hello, world!";
  }  // File closed automatically

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
}