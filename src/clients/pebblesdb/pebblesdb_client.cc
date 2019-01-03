#include "pebblesdb_client.h"

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
}

int PebblesDBClient::Read(const std::string &table, const std::string &key,
                          const std::vector<std::string> *fields,
                          std::vector<KVPair> &result) {
}

int PebblesDBClient::Scan(const std::string &table, const std::string &key,
                          int record_count,
                          const std::vector<std::string> *fields,
                          std::vector<std::vector<KVPair>> &result) {
}

int PebblesDBClient::Update(const std::string &table, const std::string &key,
                            std::vector<KVPair> &values) {
}

int PebblesDBClient::Insert(const std::string &table, const std::string &key,
                            std::vector<KVPair> &values) {
}

int PebblesDBClient::Delete(const std::string &table, const std::string &key) {
}

}  // namespace cycsb
