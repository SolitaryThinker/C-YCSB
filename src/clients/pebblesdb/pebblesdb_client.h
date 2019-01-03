#ifndef CYCSB_DB_PEBBLESDB_CLIENT_H_
#define CYCSB_DB_PEBBLESDB_CLIENT_H_

#include "core/db.h"

#include <vector>
#include "pebblesdb/db.h"
#include "pebblesdb/options.h"

namespace cycsb {

class PebblesDBClient : public DB {
  public:
    void Init();

    void Close();

    int Read(const std::string &table, const std::string &key,
             const std::vector<std::string> *fields,
             std::vector<KVPair> &result);

    int Scan(const std::string &table, const std::string &key,
             int record_count, const std::vector<std::string> *fields,
             std::vector<std::vector<KVPair>> &result);

    int Update(const std::string &table, const std::string &key,
               std::vector<KVPair> &values);

    int Insert(const std::string &table, const std::string &key,
               std::vector<KVPair> &values);

    int Delete(const std::string &table, const std::string &key);
  private:
    static leveldb::DB *db_;
};

}  // namespace cycsb

#endif  // CYCSB_DB_PEBBLESDB_CLIENT_H_
