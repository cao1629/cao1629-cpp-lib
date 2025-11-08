#pragma once
#include <fstream>
#include <string>

namespace cao1629 {

// this structure is not 9 bytes!
// compiler padding/assignment
// the actual size is 12 bytes
// how to handle this?
// -1 struct __attributed__((packed)) Record { ... }
// -2 manual serialization
struct Record {
  uint8_t op;
  int k;
  int v;
};

class LogReader {
public:
  LogReader() {}

  bool Open(std::string log);

  bool NextRecord(uint8_t *op, int *k, int *v);

  std::ifstream in_;
};

class LogWriter {
public:

  LogWriter() {}

  void Open(std::string log) {
    out_.open(log, std::ios::out | std::ios::app);
  }

  ~LogWriter() {
    out_.close();
  }

  void AppendRecord(uint8_t op, int k, int v);

  std::ofstream out_;
};

class KVStore {

public:

  KVStore(std::string log, std::string new_log) {
    // Recover from the old log
    // If it doesn't exist, no recovery work need to do.
    LogReader log_reader;
    bool existed = log_reader.Open(log);
    if (existed) {
      uint8_t op;
      int k;
      int v;

      while (log_reader.NextRecord(&op, &k, &v)) {
        if (op == 0) {
          store_.erase(k);
        } else {
          store_[k] = v;
        }
      }
    }

    // Now recovery is done.
    // Persist the current state to the new log
    log_writer.Open(new_log);
    for (auto [k, v] : store_) {
      log_writer.AppendRecord(1, k, v);
    }

    // std::filesystem::remove(log);
  }

  void Put(int k, int v);

  int Get(int k);

  void Remove(int k);

  std::unordered_map<int, int> store_;

  LogWriter log_writer;
};


void IntToByteArray(int v, char* buffer);

int ByteArrayToInt(char* buffer);

}