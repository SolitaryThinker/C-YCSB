#include "util/status.h"

namespace cycsb {

std::string Status::ToString() const {
  return "Status [name=" + name_ + ", description=" + description_ + "]";
}

const Status Status::ok = Status("OK", "The operation completely successfully.");
const Status Status::error = Status("ERROR", "The operation failed.");
const Status Status::not_found = Status("NOT_FOUND", "The requested record was not found.");
const Status Status::not_implemented = Status("NOT_IMPLEMENTED", "The operation is not "
    "implemented for the current binding.");
const Status Status::unexpected_state = Status("UNEXPECTED_STATE", "The operation reported"
    " success, but the result was not as expected.");
const Status Status::bad_request = Status("BAD_REQUEST", "The request was not valid.");
const Status Status::forbidden = Status("FORBIDDEN", "The operation is forbidden.");
const Status Status::service_unavailable = Status("SERVICE_UNAVAILABLE", "Dependant "
    "service for the current binding is not available.");
const Status Status::batched_ok = Status("BATCHED_OK", "The operation has been batched by "
    "the binding to be executed later.");

}  // namespace cycsb
