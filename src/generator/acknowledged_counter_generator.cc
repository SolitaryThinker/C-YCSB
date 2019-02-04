#include "generator/acknowledged_counter_generator.h"

#include "util/utils.h"

namespace cycsb {

/**
 * Make a generated counter value available via lastInt().
 */
void AcknowledgedCounterGenerator::Acknowledge(uint64_t value) {
  const int currentSlot = (int)(value & window_mask_);
  if (window_[currentSlot]) {
    throw utils::Exception("Too many unacknowledged insertion keys.");
  }

  window_[currentSlot] = true;

  if (mutex_.try_lock()) {
    // move a contiguous sequence from the window
    // over to the "limit" variable
    // Only loop through the entire window at most once.
    uint64_t beforeFirstSlot = (limit_ & window_mask_);
    uint64_t index;
    for (index = limit_ + 1; index != beforeFirstSlot; ++index) {
      int slot = (int)(index & window_mask_);
      if (!window_[slot]) {
        break;
      }

      window_[slot] = false;
    }

    limit_ = index - 1;
    mutex_.unlock();
  }
}

}  // namespace cycsb
