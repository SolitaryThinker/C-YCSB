#include "workloads/core_workload.h"

#include <climits>
#include <iostream>

#include "core/thread_state.h"
#include "generator/const_generator.h"
#include "generator/uniform_generator.h"
#include "generator/zipfian_generator.h"
#include "generator/scrambled_zipfian_generator.h"
#include "generator/skewed_latest_generator.h"
#include "util/status.h"

namespace cycsb {

using std::string;

const string CoreWorkload::tablename_property = "table";
const string CoreWorkload::tablename_default = "usertable";

const string CoreWorkload::field_count_property = "fieldcount";
const string CoreWorkload::field_count_default = "10";

const string CoreWorkload::field_length_distribution_property =
    "field_len_dist";
const string CoreWorkload::field_length_distribution_default = "constant";

const string CoreWorkload::field_length_property = "fieldlength";
const string CoreWorkload::field_length_default = "100";

const string CoreWorkload::read_all_fields_property = "readallfields";
const string CoreWorkload::read_all_fields_default = "true";

const string CoreWorkload::write_all_fields_property = "writeallfields";
const string CoreWorkload::write_all_fields_default = "false";

const string CoreWorkload::read_proportion_property = "readproportion";
const string CoreWorkload::read_proportion_default = "0.95";

const string CoreWorkload::update_proportion_property = "updateproportion";
const string CoreWorkload::update_proportion_default = "0.05";

const string CoreWorkload::insert_proportion_property = "insertproportion";
const string CoreWorkload::insert_proportion_default = "0.0";

const string CoreWorkload::scan_proportion_property = "scanproportion";
const string CoreWorkload::scan_proportion_default = "0.0";

const string CoreWorkload::readmodifywrite_proportion_property =
    "readmodifywriteproportion";
const string CoreWorkload::readmodifywrite_proportion_default = "0.0";

const string CoreWorkload::request_distribution_property =
    "requestdistribution";
const string CoreWorkload::request_distribution_default = "uniform";

const string CoreWorkload::min_scan_length_property = "minscanlength";
const string CoreWorkload::min_scan_length_default = "1";

const string CoreWorkload::max_scan_length_property = "maxscanlength";
const string CoreWorkload::max_scan_length_default = "1000";

const string CoreWorkload::scan_length_distribution_property =
    "scanlengthdistribution";
const string CoreWorkload::scan_length_distribution_default = "uniform";

const string CoreWorkload::insert_order_property = "insertorder";
const string CoreWorkload::insert_order_default = "hashed";

const string CoreWorkload::insert_start_property = "insertstart";
const string CoreWorkload::insert_start_default = "0";

const string CoreWorkload::record_count_property = "recordcount";
const string CoreWorkload::operation_count_property = "operationcount";

void CoreWorkload::Init(utils::Properties p) {
  table_name_ = p.GetProperty(tablename_property, tablename_default);

  field_count_ = std::stoi(p.GetProperty(field_count_property,
                                         field_count_property));

  // fieldnames?

  field_len_generator_ = GetFieldLenGenerator(p);

  record_count_ = std::stoi(p.GetProperty(record_count_property));
  if (record_count_ == 0) {
    record_count_ = LONG_MAX;
  }

  int min_scan_len = std::stoi(p.GetProperty(min_scan_length_property,
                                             min_scan_length_default));
  int max_scan_len = std::stoi(p.GetProperty(max_scan_length_property,
                                             max_scan_length_default));
  std::string scan_len_dist = p.GetProperty(scan_length_distribution_property,
                                            scan_length_distribution_default);

  // TODO: insert_end and insert_count
  int insert_start = std::stoi(p.GetProperty(insert_start_property,
                                             insert_start_default));

  read_all_fields_ = utils::StrToBool(p.GetProperty(read_all_fields_property,
                                                    read_all_fields_default));
  write_all_fields_ = utils::StrToBool(p.GetProperty(write_all_fields_property,
                                                     write_all_fields_default));

  // TODO: data_integrity

  // TODO: exponential generator for keychooser
  if (p.GetProperty(insert_order_property, insert_order_default) == "hashed") {
    ordered_inserts_ = false;
  } else {
    ordered_inserts_ = true;
  }

  key_sequence_ = new CounterGenerator(insert_start);
  operation_chooser_ = InitializeOperationChooser(p);

  // TODO: transaction insert key generator
  transaction_insert_key_sequence_ = new AcknowledgedCounterGenerator(record_count_);

  key_chooser_ = InitializeKeyChooser(p);

  field_chooser_ = new UniformGenerator(0, field_count_ - 1);

  if (scan_len_dist == "uniform") {
    scan_len_chooser_ = new UniformGenerator(min_scan_len, max_scan_len);
  } else if (scan_len_dist == "zipfian") {
    scan_len_chooser_ = new ZipfianGenerator(min_scan_len, max_scan_len);
  } else {
    throw utils::Exception("Distribution not allowed for scan length: " +
        scan_len_dist);
  }
  // TODO: insertion_retry_limit and insertion_retry_interval
}

std::string CoreWorkload::BuildKeyName(uint64_t key_num) {
  if (!ordered_inserts_) {
    key_num = utils::Hash(key_num);
  }
  // TODO: zeropadding
  return std::string("user").append(std::to_string(key_num));
}

inline std::string CoreWorkload::BuildSingleValue() {
  std::string value;
  // NOTE: probably can be more efficient...
  for (int i = 0; i < field_len_generator_->NextValue(); i++) {
    value += "X";
  }
  return value;
}

//ThreadState* InitThread(utils::Properties p, int my_thread_id,
                               //int thread_count) {
  //return nullptr;
//}

void CoreWorkload::CleanUp() { }

bool CoreWorkload::DoInsert(DB &db, ThreadState &thread_state) {
  uint64_t key_num = key_sequence_->NextValue();
  std::string db_key = BuildKeyName(key_num);
  std::string value = std::string(field_len_generator_->NextValue(),
                                  utils::RandomPrintChar());

  Status status;
  int num_of_retries = 0;
  while (true) {
    status = db.Insert("", db_key, value);
    if (status.IsOk()) {
      break;
    }
    // TODO: retry here if configured. Without retrying, the load process will
    // fail if one single insertion fails.
    if (++num_of_retries <= 0) {
      std::cerr << "Retrying insertion, retry count: " << num_of_retries << std::endl;
      // sleep here
    } else {
      std::cerr << "Error inserting, not retrying anymore. " << num_of_retries << std::endl;
      break;
    }
  }

  return status.IsOk();
}

bool CoreWorkload::DoTransaction(DB &db, ThreadState &thread_state) {
  Operation operation = operation_chooser_->NextValue();
  bool sucess;

  switch(operation) {
    case READ:
      sucess = DoTransactionRead(db);
      break;
    case UPDATE:
      sucess = DoTransactionUpdate(db);
      break;
    case INSERT:
      sucess = DoTransactionInsert(db);
      break;
    case SCAN:
      sucess = DoTransactionScan(db);
      break;
    case READ_MODIFY_WRITE:
      sucess = DoTransactionReadModifyWrite(db);
      break;
    default:
      sucess = false;
  }

  return sucess;
}

uint64_t CoreWorkload::NextKeynum() {
  uint64_t keynum;
  //if (keychooser instanceof ExponentialGenerator) {
    //do {
      //keynum = transactioninsertkeysequence.lastValue() - keychooser.nextValue().intValue();
    //} while (keynum < 0);
  //} else {
    do {
      keynum = key_chooser_->NextValue();
    } while (keynum > transaction_insert_key_sequence_->LastValue());
  //}
  return keynum;
}

bool CoreWorkload::DoTransactionRead(DB &db) {
  uint64_t key_num = NextKeynum();

  std::string key_name = BuildKeyName(key_num);
  std::string result;

  Status status = db.Read("", key_name, result);
  // data_integrity

  return status.IsOk();
}

bool CoreWorkload::DoTransactionUpdate(DB &db) {
  bool sucess = false;

  uint64_t key_num = NextKeynum();

  std::string key_name = BuildKeyName(key_num);
  std::string value = BuildSingleValue();

  Status status = db.Update("", key_name, value);

  return status.IsOk();
}

bool CoreWorkload::DoTransactionInsert(DB &db) {
  bool sucess = false;

  uint64_t key_num = transaction_insert_key_sequence_->NextValue();
  std::string key_name = BuildKeyName(key_num);
  std::string value = BuildSingleValue();

  Status status = db.Insert("", key_name, value);

  return status.IsOk();
}

bool CoreWorkload::DoTransactionScan(DB &db) {
  bool sucess = false;
  return sucess;
}

bool CoreWorkload::DoTransactionReadModifyWrite(DB &db) {
  bool sucess = false;
  return sucess;
}

Generator<uint64_t> *CoreWorkload::GetFieldLenGenerator(
    const utils::Properties &p) {
  string field_len_dist = p.GetProperty(field_length_distribution_property,
                                        field_length_distribution_default);
  int field_len = std::stoi(p.GetProperty(field_length_property,
                                          field_length_default));
  if(field_len_dist == "constant") {
    return new ConstGenerator(field_len);
  } else if(field_len_dist == "uniform") {
    return new UniformGenerator(1, field_len);
  } else if(field_len_dist == "zipfian") {
    return new ZipfianGenerator(1, field_len);
  } else {
    throw utils::Exception("Unknown field length distribution: " +
        field_len_dist);
  }
}

DiscreteGenerator<CoreWorkload::Operation> *
CoreWorkload::InitializeOperationChooser(utils::Properties &p) {
  using std::stod;

  DiscreteGenerator<CoreWorkload::Operation> *operation_chooser;

  const double read_proportion = stod(p.GetProperty(read_proportion_property,
                                                    read_proportion_default));
  const double update_proportion = stod(p.GetProperty(update_proportion_property,
                                                      update_proportion_default));
  const double insert_proportion = stod(p.GetProperty(insert_proportion_property,
                                                      insert_proportion_default));
  const double scan_proportion = stod(p.GetProperty(scan_proportion_property,
                                                    scan_proportion_default));
  const double readmodifywrite_proportion = stod(p.GetProperty(
        readmodifywrite_proportion_property, readmodifywrite_proportion_default));

  operation_chooser = new DiscreteGenerator<Operation>;

  if (read_proportion > 0) {
    operation_chooser_->AddValue(READ, read_proportion);
  }
  if (update_proportion > 0) {
    operation_chooser_->AddValue(UPDATE, update_proportion);
  }
  if (insert_proportion > 0) {
    operation_chooser_->AddValue(INSERT, insert_proportion);
  }
  if (scan_proportion > 0) {
    operation_chooser_->AddValue(SCAN, scan_proportion);
  }
  if (readmodifywrite_proportion > 0) {
    operation_chooser_->AddValue(READ_MODIFY_WRITE, readmodifywrite_proportion);
  }

  return operation_chooser;
}

Generator<uint64_t> *
CoreWorkload::InitializeKeyChooser(utils::Properties &p) {
  Generator<uint64_t> *key_chooser = NULL;

  std::string request_dist = p.GetProperty(request_distribution_property,
                                           request_distribution_default);

  const double insert_proportion = stod(p.GetProperty(insert_proportion_property,
                                                      insert_proportion_default));

  if (request_dist == "uniform") {
    key_chooser = new UniformGenerator(0, record_count_ - 1);

  } else if (request_dist == "zipfian") {
    // If the number of keys changes, we don't want to change popular keys.
    // So we construct the scrambled zipfian generator with a keyspace
    // that is larger than what exists at the beginning of the test.
    // If the generator picks a key that is not inserted yet, we just ignore it
    // and pick another key.
    int op_count = std::stoi(p.GetProperty(operation_count_property));
    int new_keys = (int)(op_count * insert_proportion * 2); // a fudge factor
    key_chooser = new ScrambledZipfianGenerator(record_count_ + new_keys);

  } else if (request_dist == "latest") {
    key_chooser = new SkewedLatestGenerator(insert_key_sequence_);

  } else {
    throw utils::Exception("Unknown request distribution: " + request_dist);
  }
  return key_chooser;
}

}  // namespace cycsb
