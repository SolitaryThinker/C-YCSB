#include "util/status.h"

namespace cycsb {

std::string Status::ToString() const {
  return "Status [name=" + name_ + ", description=" + description_ + "]";
}

const Status Status::OK = Status("OK", "The operation completely successfully.");
const Status Status::ERROR = Status("ERROR", "The operation failed.");
const Status Status::NOT_FOUND = Status("NOT_FOUND", "The requested record was not found.");
const Status Status::NOT_IMPLEMENTED = Status("NOT_IMPLEMENTED", "The operation is not "
    "implemented for the current binding.");
const Status Status::UNEXPECTED_STATE = Status("UNEXPECTED_STATE", "The operation reported"
    " success, but the result was not as expected.");
const Status Status::BAD_REQUEST = Status("BAD_REQUEST", "The request was not valid.");
const Status Status::FORBIDDEN = Status("FORBIDDEN", "The operation is forbidden.");
const Status Status::SERVICE_UNAVAILABLE = Status("SERVICE_UNAVAILABLE", "Dependant "
    "service for the current binding is not available.");
const Status Status::BATCHED_OK = Status("BATCHED_OK", "The operation has been batched by "
    "the binding to be executed later.");

}  // namespace cycsb
