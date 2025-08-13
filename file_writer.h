#ifndef CAO1629_CPP_LIB_FILE_WRITER_H_
#define CAO1629_CPP_LIB_FILE_WRITER_H_

#include <fstream>
#include <memory>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <vector>

namespace cao1629 {

class FileWriter {
 public:
  enum class WriteMode {
    kOverwrite,  // Overwrite existing file
    kAppend,     // Append to existing file
    kExclusive   // Fail if file exists
  };

  // Constructor
  explicit FileWriter(const std::string& filename,
                      WriteMode mode = WriteMode::kOverwrite);

  // Destructor
  ~FileWriter();

  // Disable copy constructor and assignment operator
  FileWriter(const FileWriter&) = delete;
  FileWriter& operator=(const FileWriter&) = delete;

  // Enable move constructor and assignment operator
  FileWriter(FileWriter&& other) noexcept;
  FileWriter& operator=(FileWriter&& other) noexcept;

  // Open file with specified mode
  bool Open(const std::string& filename,
            WriteMode mode = WriteMode::kOverwrite);

  // Close file
  void Close();

  // Check if file is open
  bool IsOpen() const;

  // Write string data
  bool Write(const std::string& data);

  // Write C-style string
  bool Write(const char* data);

  // Write binary data
  bool Write(const void* data, size_t size);

  // Write line with newline
  bool WriteLine(const std::string& line);

  // Write multiple lines
  bool WriteLines(const std::vector<std::string>& lines);

  // Template method to write any type that supports stream output
  template<typename T>
  bool WriteValue(const T& value) {
    if (!file_.is_open()) {
      return false;
    }

    file_ << value;
    return file_.good();
  }

  // Template method to write container of values
  template<typename Container>
  bool WriteContainer(const Container& container,
                      const std::string& delimiter = " ") {
    if (!file_.is_open()) {
      return false;
    }

    bool first = true;
    for (const auto& item : container) {
      if (!first) {
        file_ << delimiter;
      }
      file_ << item;
      first = false;
    }
    return file_.good();
  }

  // Flush buffer to file
  bool Flush();

  // Get current file position
  std::streampos Tell() const;

  // Seek to position
  bool Seek(std::streampos pos);

  // Get filename
  const std::string& GetFilename() const;

  // Get file size (only works if file is closed)
  size_t GetFileSize() const;

  // Static utility methods
  static bool FileExists(const std::string& filename);
  static bool DeleteFile(const std::string& filename);
  static size_t GetFileSize(const std::string& filename);

 private:
  std::string filename_;
  std::ofstream file_;
  WriteMode mode_;

  // Helper method to convert WriteMode to ios flags
  std::ios_base::openmode GetOpenMode(WriteMode mode) const;
};

// Exception class for file writer errors
class FileWriterException : public std::runtime_error {
 public:
  explicit FileWriterException(const std::string& message)
      : std::runtime_error("FileWriter Error: " + message) {}
};

}  // namespace cao1629

#endif  // CAO1629_CPP_LIB_FILE_WRITER_H_
