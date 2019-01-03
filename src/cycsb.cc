#include <cstring>
#include <string>
#include <iostream>
#include <vector>
#include <future>

#include "core/db.h"
#include "core/db_factory.h"
#include "core/workload.h"
#include "core/workload_factory.h"
#include "util/utils.h"
#include "util/properties.h"

void UsageMessage(const char *command);
bool StrStartWith(const char *str, const char *pre);
std::string ParseCommandLine(int argc, const char *argv[], utils::Properties &props);

int main(const int argc, const char *argv[]) {
  utils::Properties props;
  std::string file_name = ParseCommandLine(argc, argv, props);

  cycsb::DB *db = cycsb::DBFactory::CreateDB(props);
  if (!db) {
    std::cout << "Unknown database name " << props["dbname"] << std::endl;
    exit(1);
  }

  cycsb::Workload *workload = cycsb::WorkloadFactory::CreateWorkload(props);
  if (!workload) {
    std::cout << "Unknown workload class name " << props["workloadclass"] << std::endl;
    exit(1);
  }

}


std::string ParseCommandLine(int argc, const char *argv[], utils::Properties &props) {
  int argindex = 1;
  std::string filename;
  while (argindex < argc && StrStartWith(argv[argindex], "-")) {
    if (strcmp(argv[argindex], "-threads") == 0) {
      argindex++;
      if (argindex >= argc) {
        UsageMessage(argv[0]);
        exit(0);
      }
      props.SetProperty("threadcount", argv[argindex]);
      argindex++;
    } else if (strcmp(argv[argindex], "-db") == 0) {
      argindex++;
      if (argindex >= argc) {
        UsageMessage(argv[0]);
        exit(0);
      }
      props.SetProperty("dbname", argv[argindex]);
      argindex++;
    } else if (strcmp(argv[argindex], "-host") == 0) {
      argindex++;
      if (argindex >= argc) {
        UsageMessage(argv[0]);
        exit(0);
      }
      props.SetProperty("host", argv[argindex]);
      argindex++;
    } else if (strcmp(argv[argindex], "-port") == 0) {
      argindex++;
      if (argindex >= argc) {
        UsageMessage(argv[0]);
        exit(0);
      }
      props.SetProperty("port", argv[argindex]);
      argindex++;
    } else if (strcmp(argv[argindex], "-slaves") == 0) {
      argindex++;
      if (argindex >= argc) {
        UsageMessage(argv[0]);
        exit(0);
      }
      props.SetProperty("slaves", argv[argindex]);
      argindex++;
    } else if (strcmp(argv[argindex], "-P") == 0) {
      argindex++;
      if (argindex >= argc) {
        UsageMessage(argv[0]);
        exit(0);
      }
      filename.assign(argv[argindex]);
      std::ifstream input(argv[argindex]);
      try {
        props.Load(input);
      } catch (const std::string &message) {
        std::cout << message << std::endl;
        exit(0);
      }
      input.close();
      argindex++;
    } else {
      std::cout << "Unknown option '" << argv[argindex] << "'" << std::endl;
      exit(0);
    }
  }

  if (argindex == 1 || argindex != argc) {
    UsageMessage(argv[0]);
    exit(0);
  }

  return filename;
}


void UsageMessage(const char *command) {
  std::cout << "Usage: " << command << " [options]" << std::endl;
  std::cout << "Options:" << std::endl;
  std::cout << "  -threads n: execute using n threads (default: 1)" << std::endl;
  std::cout << "  -db dbname: specify the name of the DB to use (default: basic)" << std::endl;
  std::cout << "  -P propertyfile: load properties from the given file. Multiple files can" << std::endl;
  std::cout << "                   be specified, and will be processed in the order specified" << std::endl;
}


inline bool StrStartWith(const char *str, const char *pre) {
  return strncmp(str, pre, strlen(pre)) == 0;
}
