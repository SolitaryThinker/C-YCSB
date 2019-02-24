#include "pebblesdb_client.h"

#include "pebblesdb/options.h"
#include "pebblesdb/iterator.h"

#include <iostream>

namespace cycsb {

leveldb::DB *PebblesDBClient::db_ = nullptr;

/**
 * \brief Initializes the client.
 */
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

/**
 * \brief Close the client.
 */
void PebblesDBClient::Close() {
  delete db_;
}

/**
 * \brief Reads a value from database.
 *
 * \param       table  Not used
 * \param       key    Key of the entry
 * \param[out]  result Result from the read
 */
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

/**
 * \brief Scan over a range of entries in the database.
 *
#* \param       table        Not used
 * \param       key          Starting key of the scan
 * \param       entry_count  Number of entries to scan
 * \param[out]  results      Results from the scan operation
 */
Status PebblesDBClient::Scan(const std::string &table, const std::string &key,
                          int entry_count,
                          std::vector<KVPair> &results) {
  leveldb::ReadOptions options;
  leveldb::Iterator *iterator = db_->NewIterator(options);
  uint64_t count = 0;

  iterator->Seek(leveldb::Slice(key));

  while(iterator->Valid() && count < entry_count) {
    results.push_back(std::make_pair(iterator->key().ToString(),
                                     iterator->value().ToString()));
    iterator->Next();
    count++;
  }
  if (count < entry_count) {
    std::cout << "Only scanned " << count << " records out of "
      << entry_count << "." << std::endl;
  }

  return Status::ok;
}

/**
 * \brief Updates a value in the database.
 *
 * \param  table Not used
 * \param  key   Key of the entry to be updated
 * \param  value New value for the entry
 */
Status PebblesDBClient::Update(const std::string &table, const std::string &key,
                            const std::string &value) {
  return Status::not_implemented;
}

/**
 * \brief Inserts a new entry in to the database.
 *
 * \param  table Not used
 * \param  key   Key of the new entry
 * \param  value Value of the new entry
 */
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

/**
 * \brief Deletes an entry from the database.
 *
 * \param  table Not used
 * \param  key   Key of the entry to be deleted
 */
Status PebblesDBClient::Delete(const std::string &table, const std::string &key) {
  return Status::not_implemented;
}

}  // namespace cycsb
