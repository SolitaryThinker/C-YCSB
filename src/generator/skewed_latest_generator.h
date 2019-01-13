#ifndef CYCSB_GENERATOR_SKEWED_LATEST_GENERATOR_H_
#define CYCSB_GENERATOR_SKEWED_LATEST_GENERATOR_H_

#include "generator.h"

#include <atomic>
#include <cstdint>
#include "counter_generator.h"
#include "zipfian_generator.h"

namespace cycsb {

class SkewedLatestGenerator : public Generator<uint64_t> {
  public:
    SkewedLatestGenerator(CounterGenerator &counter) :
      basis_(counter), zipfian_(basis_.LastValue()) {
        NextValue();
    }

    uint64_t NextValue() override;
    uint64_t LastValue() override { return last_; }
  private:
    CounterGenerator &basis_;
    ZipfianGenerator zipfian_;
    std::atomic<uint64_t> last_;
};

inline uint64_t SkewedLatestGenerator::NextValue() {
  uint64_t max = basis_.LastValue();
  return last_ = max - zipfian_.NextLong(max);
}

}  // namespace cycsb

#endif  // CYCSB_GENERATOR_SKEWED_LATEST_GENERATOR_H_
