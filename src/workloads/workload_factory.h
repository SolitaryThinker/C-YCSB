#ifndef CYCSB_WORKLOADS_WORKLOAD_FACTORY_H_
#define CYCSB_WORKLOADS_WORKLOAD_FACTORY_H_

//#include "workload.h"
#include "core/properties.h"
#include "utils.h"

namespace cycsb {

class WorkloadFactory {
 public:
  static Workload* CreateWorkload(utils::Properties &props);
};

} // namespace cycsb

#endif // CYCSB_WORKLOADS_WORKLOAD_FACTORY_H_
