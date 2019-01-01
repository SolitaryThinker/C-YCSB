#ifndef CYCSB_WORKLOADS_WORKLOAD_FACTORY_H_
#define CYCSB_WORKLOADS_WORKLOAD_FACTORY_H_

#include "core/workload.h"
#include "util/properties.h"

namespace cycsb {

class WorkloadFactory {
 public:
  static Workload* CreateWorkload(utils::Properties &props);
};

} // namespace cycsb

#endif // CYCSB_WORKLOADS_WORKLOAD_FACTORY_H_
