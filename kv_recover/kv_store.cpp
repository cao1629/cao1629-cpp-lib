#include "kv_store.h"
#include <fstream>

namespace cao1629 {


void KVStore::Put(int k, int v) {
  log_writer.AppendRecord(1, k, v);
  store_[k] = v;
}


int KVStore::Get(int k) {
  return store_[k];
}


void KVStore::Remove(int k) {
  log_writer.AppendRecord(0, k, 0);
  store_.erase(k);
}


bool LogReader::Open(std::string log) {
  in_.open(log);
  if (in_.is_open()) {
    return true;
  }
  return false;
}

void IntToByteArray(int v, char* buffer) {
  buffer[0] = v>>24 & 0xFF;
  buffer[1] = v>>16 & 0xFF;
  buffer[2] = v>>8 & 0xFF;
  buffer[3] = v &0xFF;
}


int ByteArrayToInt(char* buffer) {
  return buffer[0] << 24 | buffer[1] << 16 | buffer[2] << 8 | buffer[3];
}

bool LogReader::NextRecord(uint8_t *op, int *k, int *v) {
  int val = in_.get();
  if (val < 0) {
    return false;
  }
  *op = val;

  char buffer[4];
  in_.read(buffer, 4);
  if (in_.eof() || in_.gcount() < 4) {
    return false;
  }
  *k = ByteArrayToInt(buffer);

  in_.read(buffer, 4);
  if (in_.eof() || in_.gcount() < 4) {
    return false;
  }
  *v = ByteArrayToInt(buffer);
  return true;
}


void LogWriter::AppendRecord(uint8_t op, int k, int v) {
  out_.put(op);

  char buffer[4];
  IntToByteArray(k, buffer);
  out_.write(buffer, 4);

  IntToByteArray(v, buffer);
  out_.write(buffer, 4);
}





}