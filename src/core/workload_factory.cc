#include "workload_factory.h"

#include "core/workload.h"
#include "core/db.h"

#include "workloads/core_workload.h"

namespace cycsb {

Workload* WorkloadFactory::CreateWorkload(utils::Properties &props) {
  if (props["workload"] == "coreworkload") {
    return new CoreWorkload;
  } else {
    return NULL;
  }
}

}
