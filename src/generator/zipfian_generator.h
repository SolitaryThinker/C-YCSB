#ifndef CYCSB_GENERATOR_ZIPFIAN_GENERATOR_H_
#define CYCSB_GENERATOR_ZIPFIAN_GENERATOR_H_

#include "generator.h"

#include <cstdint>
#include <cmath>
#include <mutex>

namespace cycsb {

class ZipfianGenerator : public Generator<uint64_t> {
  public:
    static constexpr double const kZipfianConst = 0.99;

    ZipfianGenerator(uint64_t items) : ZipfianGenerator(0, items - 1) {
    }

    ZipfianGenerator(uint64_t min, uint64_t max)
      : ZipfianGenerator(min, max, kZipfianConst) {
    }

    ZipfianGenerator(uint64_t min, uint64_t max, double zipfian_const)
      : ZipfianGenerator(min, max, kZipfianConst,
                         ZetaStatic(max - min + 1, zipfian_const)) {
    }

    ZipfianGenerator(uint64_t min, uint64_t max, double zipfian_const,
                     double zetan)
      : items_(max - min + 1),
        base_(min),
        zipfian_const_(zipfian_const),
        theta_(zipfian_const),
        zeta_to_theta_(Zeta(2, theta_)),
        alpha_(1.0 / (1.0 - theta_)),
        zetan_(zetan),
        count_for_zeta_(items_),
        eta_((1 - std::pow(2.0 / items_, 1 - theta_))
             / (1 - zeta_to_theta_ / zetan_)) {
    }

    uint64_t NextLong(uint64_t item_count);
    uint64_t NextValue() override;
    uint64_t LastValue() override;

   private:
    static double ZetaStatic(uint64_t n, double theta);
    static double ZetaStatic(uint64_t st, uint64_t n, double theta,
        double initial_sum);
    double Zeta(uint64_t n, double theta);
    double Zeta(uint64_t st, uint64_t n, double theta, double initial_sum);

    uint64_t items_, base_, count_for_zeta_;
    double zipfian_const_, theta_, zeta_to_theta_, alpha_, zetan_, eta_;
    std::mutex mutex_;
    uint64_t last_value_;
    bool allow_item_count_decrease_ = false;
};

}  // cycsb

#endif  // CYCSB_GENERATOR_ZIPFIAN_GENERATOR_H_
