#ifndef CYCSB_DB_PEBBLESDB_CLIENT_H_
#define CYCSB_DB_PEBBLESDB_CLIENT_H_

#include "core/db.h"

#include <vector>
#include "pebblesdb/db.h"

namespace cycsb {

class PebblesDBClient : public DB {
  public:
    void Init() override;

    void Close() override;

    int Read(const std::string &table, const std::string &key,
             std::string &result) override;

    int Scan(const std::string &table, const std::string &key,
             int record_count,
             std::vector<std::vector<KVPair>> &results) override;

    int Update(const std::string &table, const std::string &key,
               const std::string &value) override;

    int Insert(const std::string &table, const std::string &key,
               const std::string &values) override;

    int Delete(const std::string &table, const std::string &key) override;
  private:
    static leveldb::DB *db_;
};

}  // namespace cycsb

#endif  // CYCSB_DB_PEBBLESDB_CLIENT_H_
