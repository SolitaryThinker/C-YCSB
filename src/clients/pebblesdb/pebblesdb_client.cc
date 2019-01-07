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
                                               "pebblesdb_database", &db_);
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

  leveldb::Status status = db_->Get(options, key, &result);
  if (status.ok()) {
    return Status::ok;
  } else {
    // TODO: add support for other status types
    return Status::error;
  }
}

Status PebblesDBClient::Scan(const std::string &table, const std::string &key,
                          int record_count,
                          std::vector<std::vector<KVPair>> &results) {
  return Status::not_implemented;
}

Status PebblesDBClient::Update(const std::string &table, const std::string &key,
                            const std::string &value) {
  return Status::not_implemented;
}

Status PebblesDBClient::Insert(const std::string &table, const std::string &key,
                            const std::string &value) {
  leveldb::WriteOptions options;

  leveldb::Status status = db_->Put(options, key, leveldb::Slice(value));
  if (status.ok()) {
    return Status::ok;
  } else {
    // TODO: add support for other status types
    return Status::error;
  }
}

Status PebblesDBClient::Delete(const std::string &table, const std::string &key) {
  return Status::not_implemented;
}

}  // namespace cycsb
