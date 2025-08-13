#include "file_writer.h"

#include <iostream>
#include <string>
#include <vector>

using cao1629::FileWriter;
using cao1629::FileWriterException;

void TestBasicWriting() {
  std::cout << "Testing basic file writing...\n";

  try {
    FileWriter writer("test_output.txt", FileWriter::WriteMode::kOverwrite);

    // Write different types of data
    writer.Write("Hello, World!\n");
    writer.WriteLine("This is a line with automatic newline");
    writer.WriteValue(42);
    writer.Write(" ");
    writer.WriteValue(3.14159);
    writer.WriteLine("");

    // Write multiple lines
    std::vector<std::string> lines = {
        "Line 1",
        "Line 2",
        "Line 3"
    };
    writer.WriteLines(lines);

    // Write container data
    std::vector<int> numbers = {1, 2, 3, 4, 5};
    writer.WriteContainer(numbers, ", ");
    writer.WriteLine("");

    writer.Flush();
    std::cout << "Basic writing test completed successfully!\n";

  } catch (const FileWriterException& e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }
}

void TestAppendMode() {
  std::cout << "\nTesting append mode...\n";

  try {
    FileWriter writer("test_output.txt", FileWriter::WriteMode::kAppend);
    writer.WriteLine("This line was appended!");
    writer.WriteLine("And this one too!");

    std::cout << "Append mode test completed successfully!\n";

  } catch (const FileWriterException& e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }
}

void TestBinaryWriting() {
  std::cout << "\nTesting binary data writing...\n";

  try {
    FileWriter writer("binary_test.bin", FileWriter::WriteMode::kOverwrite);

    // Write binary data
    int data[] = {1, 2, 3, 4, 5};
    writer.Write(data, sizeof(data));

    // Write individual bytes
    char bytes[] = {'A', 'B', 'C', 'D'};
    writer.Write(bytes, sizeof(bytes));

    std::cout << "Binary writing test completed successfully!\n";

  } catch (const FileWriterException& e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }
}

void TestExclusiveMode() {
  std::cout << "\nTesting exclusive mode...\n";

  try {
    // First attempt should succeed (file doesn't exist)
    FileWriter writer1("exclusive_test.txt", FileWriter::WriteMode::kExclusive);
    writer1.WriteLine("First write in exclusive mode");
    writer1.Close();

    // Second attempt should fail (file exists)
    try {
      FileWriter writer2("exclusive_test.txt", FileWriter::WriteMode::kExclusive);
      std::cout << "ERROR: Should have failed!\n";
    } catch (const FileWriterException& e) {
      std::cout << "Correctly caught exception: " << e.what() << std::endl;
    }

    std::cout << "Exclusive mode test completed successfully!\n";

  } catch (const FileWriterException& e) {
    std::cerr << "Unexpected error: " << e.what() << std::endl;
  }
}

void TestFileUtilities() {
  std::cout << "\nTesting file utility functions...\n";

  // Check if file exists
  bool exists = FileWriter::FileExists("test_output.txt");
  std::cout << "test_output.txt exists: " << (exists ? "Yes" : "No") << std::endl;

  // Get file size
  if (exists) {
    size_t size = FileWriter::GetFileSize("test_output.txt");
    std::cout << "File size: " << size << " bytes\n";
  }

  // Test move semantics
  FileWriter writer("move_test.txt");
  writer.WriteLine("Testing move semantics");

  // Move constructor
  FileWriter moved_writer = std::move(writer);
  moved_writer.WriteLine("Moved writer is working!");

  std::cout << "File utility tests completed successfully!\n";
}

void CleanupTestFiles() {
  std::cout << "\nCleaning up test files...\n";

  std::vector<std::string> test_files = {
      "test_output.txt",
      "binary_test.bin",
      "exclusive_test.txt",
      "move_test.txt"
  };

  for (const auto& filename : test_files) {
    if (FileWriter::FileExists(filename)) {
      bool deleted = FileWriter::DeleteFile(filename);
      std::cout << "Deleted " << filename << ": "
                << (deleted ? "Success" : "Failed") << std::endl;
    }
  }
}

int main() {
  std::cout << "FileWriter Class Test Suite\n";
  std::cout << "===========================\n";

  TestBasicWriting();
  TestAppendMode();
  TestBinaryWriting();
  TestExclusiveMode();
  TestFileUtilities();

  // Uncomment the next line if you want to clean up test files
  // CleanupTestFiles();

  std::cout << "\nAll tests completed!\n";
  return 0;
}
