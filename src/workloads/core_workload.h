//
//  core_workload.h
//  CYCSB
//
//  Created by Jinglei Ren on 12/9/14.
//  Modified by William Lin
//  Copyright (c) 2014 Jinglei Ren <jinglei@ren.systems>.
//

#ifndef CYCSB_WORKLOADS_CORE_WORKLOAD_H_
#define CYCSB_WORKLOADS_CORE_WORKLOAD_H_

#include "generator/generator.h"
#include "generator/discrete_generator.h"
#include "generator/counter_generator.h"
#include "core/workload.h"

namespace cycsb {

class CoreWorkload : public Workload {
  public:
    ///
    /// Transaction operations supported
    ///
    enum Operation {
      INSERT,
      READ,
      UPDATE,
      SCAN,
      READ_MODIFY_WRITE
    };

    ///
    /// The name of the database table to run queries against.
    ///
    static const std::string tablename_property;
    static const std::string tablename_default;

    ///
    /// The name of the property for the number of fields in a record.
    ///
    static const std::string field_count_property;
    static const std::string field_count_default;

    ///
    /// The name of the property for the field length distribution.
    /// Options are "uniform", "zipfian" (favoring short records), and "constant".
    ///
    static const std::string field_length_distribution_property;
    static const std::string field_length_distribution_default;

    ///
    /// The name of the property for the length of a field in bytes.
    ///
    static const std::string field_length_property;
    static const std::string field_length_default;

    ///
    /// The name of the property for deciding whether to read one field (false)
    /// or all fields (true) of a record.
    ///
    static const std::string read_all_fields_property;
    static const std::string read_all_fields_default;

    ///
    /// The name of the property for deciding whether to write one field (false)
    /// or all fields (true) of a record.
    ///
    static const std::string write_all_fields_property;
    static const std::string write_all_fields_default;

    ///
    /// The name of the property for the proportion of read transactions.
    ///
    static const std::string read_proportion_property;
    static const std::string read_proportion_default;

    ///
    /// The name of the property for the proportion of update transactions.
    ///
    static const std::string update_proportion_property;
    static const std::string update_proportion_default;

    ///
    /// The name of the property for the proportion of insert transactions.
    ///
    static const std::string insert_proportion_property;
    static const std::string insert_proportion_default;

    ///
    /// The name of the property for the proportion of scan transactions.
    ///
    static const std::string scan_proportion_property;
    static const std::string scan_proportion_default;

    ///
    /// The name of the property for the proportion of
    /// read-modify-write transactions.
    ///
    static const std::string readmodifywrite_proportion_property;
    static const std::string readmodifywrite_proportion_default;

    ///
    /// The name of the property for the the distribution of request keys.
    /// Options are "uniform", "zipfian" and "latest".
    ///
    static const std::string request_distribution_property;
    static const std::string request_distribution_default;

    ///
    /// The name of the property for the min scan length (number of records).
    ///
    static const std::string min_scan_length_property;
    static const std::string min_scan_length_default;

    ///
    /// The name of the property for the max scan length (number of records).
    ///
    static const std::string max_scan_length_property;
    static const std::string max_scan_length_default;

    ///
    /// The name of the property for the scan length distribution.
    /// Options are "uniform" and "zipfian" (favoring short scans).
    ///
    static const std::string scan_length_distribution_property;
    static const std::string scan_length_distribution_default;

    ///
    /// The name of the property for the order to insert records.
    /// Options are "ordered" or "hashed".
    ///
    static const std::string insert_order_property;
    static const std::string insert_order_default;

    static const std::string insert_start_property;
    static const std::string insert_start_default;

    static const std::string record_count_property;
    static const std::string operation_count_property;

    ///
    /// Initialize the scenario.
    /// Called once, in the main client thread, before any operations are started.
    ///
    void Init(utils::Properties p) override;


    //ThreadState* InitThread(utils::Properties p, int my_thread_id,
                                   //int thread_count) {
      //return nullptr;
    //}

    void CleanUp() override;

    bool DoInsert(DB &db, ThreadState &thread_state) override;

    bool DoTransaction(DB &db, ThreadState &thread_state) override;

    bool DoTransactionRead(DB &db);
    bool DoTransactionUpdate(DB &db);
    bool DoTransactionInsert(DB &db);
    bool DoTransactionScan(DB &db);
    bool DoTransactionReadModifyWrite(DB &db);

    CoreWorkload() :
      field_count_(0), read_all_fields_(false), write_all_fields_(false),
      field_len_generator_(NULL), key_sequence_(NULL), operation_chooser_(NULL),
      key_chooser_(NULL), field_chooser_(NULL), scan_len_chooser_(NULL),
      insert_key_sequence_(3), ordered_inserts_(true), record_count_(0) {
    }

    virtual ~CoreWorkload() {
      if (field_len_generator_) delete field_len_generator_;
      if (key_sequence_) delete key_sequence_;
      if (operation_chooser_) delete operation_chooser_;
      if (key_chooser_) delete key_chooser_;
      if (field_chooser_) delete field_chooser_;
      if (scan_len_chooser_) delete scan_len_chooser_;
    }

  protected:
    std::string BuildKeyName(uint64_t key_num);

    Generator<uint64_t> *GetFieldLenGenerator(const utils::Properties &p);
    DiscreteGenerator<Operation> *InitializeOperationChooser(utils::Properties &p);
    Generator<uint64_t> *InitializeKeyChooser(utils::Properties &p);

    std::string table_name_;
    int field_count_;
    bool read_all_fields_;
    bool write_all_fields_;
    Generator<uint64_t> *field_len_generator_;
    Generator<uint64_t> *key_sequence_;
    DiscreteGenerator<Operation> *operation_chooser_;
    Generator<uint64_t> *key_chooser_;
    Generator<uint64_t> *field_chooser_;
    Generator<uint64_t> *scan_len_chooser_;
    CounterGenerator insert_key_sequence_;
    bool ordered_inserts_;
    uint64_t record_count_;
};

}  // namespace cycsb

#endif  // CYCSB_WORKLOADS_CORE_WORKLOAD_H_
