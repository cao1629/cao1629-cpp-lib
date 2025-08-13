#include "file_writer.h"

#include <filesystem>
#include <iostream>

namespace cao1629 {

FileWriter::FileWriter(const std::string& filename, WriteMode mode)
    : filename_(filename), mode_(mode) {
  if (!Open(filename, mode)) {
    throw FileWriterException("Failed to open file: " + filename);
  }
}

FileWriter::~FileWriter() {
  Close();
}

FileWriter::FileWriter(FileWriter&& other) noexcept
    : filename_(std::move(other.filename_)),
      file_(std::move(other.file_)),
      mode_(other.mode_) {
  other.filename_.clear();
}

FileWriter& FileWriter::operator=(FileWriter&& other) noexcept {
  if (this != &other) {
    Close();
    filename_ = std::move(other.filename_);
    file_ = std::move(other.file_);
    mode_ = other.mode_;
    other.filename_.clear();
  }
  return *this;
}

bool FileWriter::Open(const std::string& filename, WriteMode mode) {
  Close();  // Close any existing file

  filename_ = filename;
  mode_ = mode;

  // Check if file exists when using EXCLUSIVE mode
  if (mode == WriteMode::kExclusive && FileExists(filename)) {
    return false;
  }

  std::ios_base::openmode open_mode = GetOpenMode(mode);
  file_.open(filename, open_mode);

  return file_.is_open();
}

void FileWriter::Close() {
  if (file_.is_open()) {
    file_.close();
  }
}

bool FileWriter::IsOpen() const {
  return file_.is_open();
}

bool FileWriter::Write(const std::string& data) {
  if (!file_.is_open()) {
    return false;
  }

  file_ << data;
  return file_.good();
}

bool FileWriter::Write(const char* data) {
  if (!file_.is_open() || !data) {
    return false;
  }

  file_ << data;
  return file_.good();
}

bool FileWriter::Write(const void* data, size_t size) {
  if (!file_.is_open() || !data || size == 0) {
    return false;
  }

  file_.write(static_cast<const char*>(data), size);
  return file_.good();
}

bool FileWriter::WriteLine(const std::string& line) {
  if (!file_.is_open()) {
    return false;
  }

  file_ << line << '\n';
  return file_.good();
}

bool FileWriter::WriteLines(const std::vector<std::string>& lines) {
  if (!file_.is_open()) {
    return false;
  }

  for (const auto& line : lines) {
    file_ << line << '\n';
    if (!file_.good()) {
      return false;
    }
  }
  return true;
}

bool FileWriter::Flush() {
  if (!file_.is_open()) {
    return false;
  }

  file_.flush();
  return file_.good();
}

std::streampos FileWriter::Tell() const {
  if (!file_.is_open()) {
    return -1;
  }

  return file_.tellp();
}

bool FileWriter::Seek(std::streampos pos) {
  if (!file_.is_open()) {
    return false;
  }

  file_.seekp(pos);
  return file_.good();
}

const std::string& FileWriter::GetFilename() const {
  return filename_;
}

size_t FileWriter::GetFileSize() const {
  if (file_.is_open()) {
    return 0;  // Can't get size of open file reliably
  }

  return GetFileSize(filename_);
}

bool FileWriter::FileExists(const std::string& filename) {
  return std::filesystem::exists(filename);
}

bool FileWriter::DeleteFile(const std::string& filename) {
  try {
    return std::filesystem::remove(filename);
  } catch (const std::filesystem::filesystem_error&) {
    return false;
  }
}

size_t FileWriter::GetFileSize(const std::string& filename) {
  try {
    return std::filesystem::file_size(filename);
  } catch (const std::filesystem::filesystem_error&) {
    return 0;
  }
}

std::ios_base::openmode FileWriter::GetOpenMode(WriteMode mode) const {
  switch (mode) {
    case WriteMode::kOverwrite:
      return std::ios::out | std::ios::trunc;
    case WriteMode::kAppend:
      return std::ios::out | std::ios::app;
    case WriteMode::kExclusive:
      return std::ios::out | std::ios::trunc;
    default:
      return std::ios::out | std::ios::trunc;
  }
}

}  // namespace cao1629
