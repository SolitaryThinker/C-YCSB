#ifndef CYCSB_UTIL_STATUS_H_
#define CYCSB_UTIL_STATUS_H_

#include <string>

namespace cycsb {

class Status {
  public:
    Status(std::string name, std::string description)
    : name_(name),
      description_(description_) {
    }

    bool operator==(const Status &other_status);
    bool operator!=(const Status &other_status);

    bool IsOk() { return *this == OK || *this == BATCHED_OK; }

    std::string GetName() const { return name_; }
    std::string GetDescription() const { return description_; }

    std::string ToString() const;

    static const Status OK;
    static const Status ERROR;
    static const Status NOT_FOUND;
    static const Status NOT_IMPLEMENTED;
    static const Status UNEXPECTED_STATE;
    static const Status BAD_REQUEST;
    static const Status FORBIDDEN;
    static const Status SERVICE_UNAVAILABLE;
    static const Status BATCHED_OK;

  private:
    const std::string name_;
    const std::string description_;
};

bool Status::operator==(const Status &other_status) {
  return name_ == other_status.name_ &&
         description_ == other_status.description_;
}

bool Status::operator!=(const Status &other_status) {
  return !(*this == other_status);
}

}  // namespace cycsb

#endif  // CYCSB_UTIL_STATUS_H_
