#include "workload_factory.h"

//#include "workloads/core_workload.h"
#include "utils.h"

//using namespace std;
using ycsbc::Workload;
using ycsbc::WorkloadFactory;

DB* DBFactory::CreateDB(utils::Properties &props) {
  if (props["workload"] == "coreworkload") {
    return new PebblesDB;
  } else {
    return NULL;
  }
}
