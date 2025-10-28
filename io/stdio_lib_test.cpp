#include <gtest/gtest.h>
#include <cstdio>
#include <fstream>
#include <filesystem>


namespace cao1629 {


TEST(StdioTest, WriteWithFopen) {
  const char* filename = "test_fopen.txt";

  // Create and write to file using fopen
  FILE* file = fopen(filename, "w");
  ASSERT_NE(file, nullptr);

  const char* message = "Hello, world!";
  size_t written = fwrite(message, sizeof(char), strlen(message), file);
  EXPECT_EQ(written, strlen(message));

  fclose(file);

  // Verify the file content
  file = fopen(filename, "r");
  ASSERT_NE(file, nullptr);

  char buffer[100] = {0};

  fgets(buffer, sizeof(buffer), file);
  EXPECT_STREQ(buffer, "Hello, world!");

  fclose(file);

  // Clean up
  std::remove(filename);
}

TEST(StdioTest, TestAppendPlus) {
  const char* filename = "test_fopen.txt";
  FILE* file = fopen(filename, "a+");
  ASSERT_NE(file, nullptr);

  const char* message = "Hello, world!";
  size_t written = fwrite(message, sizeof(char), strlen(message), file);
  EXPECT_EQ(written, strlen(message));

  fseek(file, 0, SEEK_SET);
  char buffer[100] = {0};
  fgets(buffer, sizeof(buffer), file);
  EXPECT_STREQ(buffer, "Hello, world!");

  fclose(file);
  std::remove(filename);
}


TEST(StdioTest, TestFseek) {
  std::ofstream("dummy.nfo") << "8 bytes\n"; // create the file

  // "b" means in binary mode, but it has no effect on POSIX systems.
  // It only has effect on Windows systems.
  std::FILE* fp = std::fopen("dummy.nfo", "rb");
  assert(fp);

  // Get the size of the file.
  std::fseek(fp, 0, SEEK_END); // seek to end
  const std::size_t filesize = std::ftell(fp);
  std::vector<std::uint8_t> buffer(filesize);

  // Another way of getting a file's size
  auto filesize2 = std::filesystem::file_size("dummy.nfo");
  EXPECT_EQ(filesize, filesize2);

  std::fseek(fp, 0, SEEK_SET); // seek to start
  std::fread(buffer.data(), sizeof(std::uint8_t), buffer.size(), fp);

  std::fclose(fp);
  std::printf("I've read %zi bytes\n", filesize);
}

}

