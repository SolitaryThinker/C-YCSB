#include "workloads/core_workload.h"

#include "core/thread_state.h"

namespace cycsb {

void CoreWorkload::Init(utils::Properties p) { }

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
