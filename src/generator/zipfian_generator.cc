#include "zipfian_generator.h"

#include "util/utils.h"

namespace cycsb {

uint64_t ZipfianGenerator::NextLong(uint64_t item_count) {
  if (item_count != count_for_zeta_) {
    std::lock_guard<std::mutex> lock(mutex_);
    if (item_count > count_for_zeta_) {
      zetan_ = Zeta(count_for_zeta_, item_count, theta_, zetan_);
      eta_ = (1 - std::pow(2.0 / items_, 1 - theta_)) / (1 - zeta_to_theta_ / zetan_);
    } else if ((item_count < count_for_zeta_) && (allow_item_count_decrease_)) {
      //TODO: comments
      zetan_ = Zeta(item_count, theta_);
      eta_ = (1 - std::pow(2.0 / items_, 1 - theta_)) / (1 - zeta_to_theta_ / zetan_);
    }
  }

  double u = utils::RandomDouble();
  double uz = u * zetan_;

  if (uz < 1.0) {
    return base_;
  }

  if (uz < 1.0 + std::pow(0.5, theta_)) {
    return base_ + 1;
  }

  uint64_t ret = base_ + (uint64_t)(item_count * std::pow(eta_ * u - eta_ + 1, alpha_));
  //setLastValue(ret);
  return ret;
}

uint64_t ZipfianGenerator::NextValue() {
  return NextLong(items_);
}

double ZipfianGenerator::ZetaStatic(uint64_t n, double theta) {
  return ZetaStatic(0, n, theta, 0);
}

double ZipfianGenerator::ZetaStatic(uint64_t st, uint64_t n, double theta,
                                    double initial_sum) {
  double sum = initial_sum;
  for (uint64_t i = st; i < n; ++i) {
    sum += 1 / (std::pow(i + 1, theta));
  }

  return sum;
}

double ZipfianGenerator::Zeta(uint64_t n, double theta) {
  count_for_zeta_ = n;
  return ZetaStatic(n, theta);
}

double ZipfianGenerator::Zeta(uint64_t st, uint64_t n, double theta,
                              double initial_sum) {
  count_for_zeta_ = n;
  return ZetaStatic(st, n, theta, initial_sum);
}

}  // namespace cycsb
