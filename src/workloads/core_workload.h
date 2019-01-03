#ifndef CYCSB_WORKLOADS_CORE_WORKLOAD_H_
#define CYCSB_WORKLOADS_CORE_WORKLOAD_H_

#include "core/workload.h"

namespace cycsb {

class CoreWorkload : public Workload {
  public:
    void Init(utils::Properties p);

    //ThreadState* InitThread(utils::Properties p, int my_thread_id,
                                   //int thread_count) {
      //return nullptr;
    //}

    void CleanUp();

    bool DoInsert(DB &db, ThreadState &thread_state);

    bool DoTransaction(DB &db, ThreadState &thread_state);
};

}  // namespace cycsb

#endif  // CYCSB_WORKLOADS_CORE_WORKLOAD_H_
