#ifndef CYCSB_UTIL_NOT_IMPLEMENTED_H_
#define CYCSB_UTIL_NOT_IMPLEMENTED_H_

#include <stdexcept>

namespace util {

class NotImplementedException : public std::logic_error {
  public:
    NotImplementedException()
      : std::logic_error("Function not yet implemented.") { }
};

}  // namespace util

#endif  // CYCSB_UTIL_NOT_IMPLEMENTED_H_
