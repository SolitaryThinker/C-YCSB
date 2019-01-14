#ifndef CYCSB_UTIL_STATUS_H_
#define CYCSB_UTIL_STATUS_H_

#include <string>

namespace cycsb {

class Status {
  public:
    Status() {
    }

    Status(std::string name, std::string description)
    : name_(name),
      description_(description_) {
    }

    bool operator==(const Status &other_status);
    bool operator!=(const Status &other_status);
    Status& operator=(const Status &s);

    bool IsOk() { return *this == ok || *this == batched_ok; }

    std::string GetName() const { return name_; }
    std::string GetDescription() const { return description_; }

    std::string ToString() const;

    static const Status ok;
    static const Status error;
    static const Status not_found;
    static const Status not_implemented;
    static const Status unexpected_state;
    static const Status bad_request;
    static const Status forbidden;
    static const Status service_unavailable;
    static const Status batched_ok;

  private:
    std::string name_;
    std::string description_;
};

inline bool Status::operator==(const Status &other_status) {
  return name_ == other_status.name_ &&
         description_ == other_status.description_;
}

inline bool Status::operator!=(const Status &other_status) {
  return !(*this == other_status);
}

inline Status& Status::operator=(const Status &s) {
  if (name_ != s.name_) {
    name_ = s.name_;
  }

  if (description_ != s.description_) {
    description_ = s.description_;
  }

  return *this;
}

}  // namespace cycsb

#endif  // CYCSB_UTIL_STATUS_H_
