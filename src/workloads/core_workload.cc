#include "workloads/core_workload.h"

#include "core/thread_state.h"
#include "generator/const_generator.h"
#include "generator/uniform_generator.h"
#include "generator/zipfian_generator.h"

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

  field_len_generator_ = GetFieldLenGenerator(p);
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

//ThreadState* InitThread(utils::Properties p, int my_thread_id,
                               //int thread_count) {
  //return nullptr;
//}

void CoreWorkload::CleanUp() { }

bool CoreWorkload::DoInsert(DB &db, ThreadState &thread_state) {
}

bool CoreWorkload::DoTransaction(DB &db, ThreadState &thread_state) {
}

}  // namespace cycsb
