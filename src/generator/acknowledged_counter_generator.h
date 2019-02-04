#ifndef CYCSB_GENERATOR_ACKNOWLEDGED_COUNTER_GENERATOR_H_
#define CYCSB_GENERATOR_ACKNOWLEDGED_COUNTER_GENERATOR_H_

#include <string>
#include <mutex>

#include "generator/counter_generator.h"

namespace cycsb {

class AcknowledgedCounterGenerator : public CounterGenerator {
  public:
    AcknowledgedCounterGenerator(uint64_t start)
      : CounterGenerator(start),
        limit_(start - 1) {
    }
    uint64_t LastValue() override { return limit_; }
    void Acknowledge(uint64_t value);

    static const uint64_t window_size = 1 << 20;

  private:
    static const uint64_t window_mask_ = window_size - 1;
    bool window_[window_size];
    volatile uint64_t limit_;
    std::mutex mutex_;
};

}  // namespace cycsb

#endif  // CYCSB_GENERATOR_ACKNOWLEDGED_COUNTER_GENERATOR_H_
