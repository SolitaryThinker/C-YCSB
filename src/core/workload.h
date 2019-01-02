#ifndef CYCSB_WORKLOAD_H_
#define CYCSB_WORKLOAD_H_

#include <atomic>
#include "core/db.h"
#include "core/thread_state.h"
#include "util/properties.h"

namespace cycsb {


class Workload {
  public:
    static const std::string kInsertStartProperty = "insertstart";
    static const std::string kInsertCountProperty = "insertstart";

    static const std::string kInsertStartPropertyDefault = "0";

    enum Operation {
      INSERT,
      READ,
      UPDATE,
      SCAN,
      READMODIFYWRITE
    };

    virtual void Init(utils::Properties p) { }

    virtual ThreadState* InitThread(utils::Properties p, int my_thread_id,
                                   int thread_count) {
      return nullptr;
    }

    virtual void CleanUp() { }

    virtual bool DoInsert(DB &db, ThreadState &thread_state) = 0;

    virtual bool DoTransaction(DB &db, ThreadState &thread_state) = 0;

    virtual void RequestStop() {
      stop_requested_ = true;
    }

    virtual bool IsStopRequested() {
      return stop_requested_;
    }
  private:
    std::atomic<bool> stop_requested_ = false;
};

}  // namespace cycsb

#endif  // CYCSB_WORKLOAD_H_
