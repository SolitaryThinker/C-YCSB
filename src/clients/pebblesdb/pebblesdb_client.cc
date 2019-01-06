#include "pebblesdb_client.h"

#include "pebblesdb/options.h"

#include <iostream>

namespace cycsb {

leveldb::DB *PebblesDBClient::db_ = nullptr;

void PebblesDBClient::Init() {
  if (db_ == nullptr) {
    leveldb::Options options;
    options.create_if_missing = true;

    leveldb::Status status = leveldb::DB::Open(options,
                                               "tmp/pebblesdb_database", &db_);
    if (!status.ok()) {
      std::cout << "Failed to open database" << std::endl;
    }
  }
}

void PebblesDBClient::Close() {
  delete db_;
}

Status PebblesDBClient::Read(const std::string &table, const std::string &key,
                          std::string &result) {
  leveldb::ReadOptions options;
  if (db_->Get(options, key, &result).ok()) {
    return Status::ok;
  } else {
    // TODO: add support for other status types
    return Status::error;
  }
}

Status PebblesDBClient::Scan(const std::string &table, const std::string &key,
                          int record_count,
                          std::vector<std::vector<KVPair>> &results) {
}

Status PebblesDBClient::Update(const std::string &table, const std::string &key,
                            const std::string &value) {
}

Status PebblesDBClient::Insert(const std::string &table, const std::string &key,
                            const std::string &value) {

}

Status PebblesDBClient::Delete(const std::string &table, const std::string &key) {
}

}  // namespace cycsb
