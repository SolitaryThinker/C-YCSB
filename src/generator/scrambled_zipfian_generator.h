//
//  scrambled_zipfian_generator.h
//  CYCSB
//
//  Created by Jinglei Ren on 12/8/14.
//  Modified by William Lin
//  Copyright (c) 2014 Jinglei Ren <jinglei@ren.systems>.
//

#ifndef CYCSB_GENERATORS_SCRAMBLED_ZIPFIAN_GENERATOR_H_
#define CYCSB_GENERATORS_SCRAMBLED_ZIPFIAN_GENERATOR_H_

#include <atomic>
#include <cstdint>

#include "generator/generator.h"
#include "generator/zipfian_generator.h"
#include "util/utils.h"

namespace cycsb {

class ScrambledZipfianGenerator : public Generator<uint64_t> {
  public:
    static constexpr double const zetan = 26.46902820178302;
    static constexpr double const used_zipfian_constant = 0.99;
    static constexpr long const item_count = 10000000000L;

    ScrambledZipfianGenerator(uint64_t num_items)
      : ScrambledZipfianGenerator((uint64_t)0, num_items - 1) {
    }

    ScrambledZipfianGenerator(uint64_t min, uint64_t max)
      : ScrambledZipfianGenerator(min, max, ZipfianGenerator::zipfian_constant) {
    }

    ScrambledZipfianGenerator(uint64_t min, uint64_t max, double zipfian_const)
      : min_(min),
        max_(max),
        item_count_(max - min + 1) {
      if (zipfian_const == used_zipfian_constant) {
        generator_ = new ZipfianGenerator(0, item_count, zipfian_const, zetan);
      } else {
        generator_ = new ZipfianGenerator(0, item_count, zipfian_const);
      }
    }

    ~ScrambledZipfianGenerator() {
      if (generator_) delete generator_;
    }

    uint64_t NextValue();
    uint64_t LastValue();

  private:
    uint64_t min_, max_, item_count_;
    ZipfianGenerator *generator_;

    uint64_t Scramble(uint64_t value) const;
};

inline uint64_t ScrambledZipfianGenerator::Scramble(uint64_t value) const {
  return min_ + utils::FNVHash64(value) % item_count_;
}

inline uint64_t ScrambledZipfianGenerator::NextValue() {
  return Scramble(generator_->NextValue());
}

inline uint64_t ScrambledZipfianGenerator::LastValue() {
  return Scramble(generator_->LastValue());
}

}  // namespace cycsb

#endif  // CYCSB_GENERATORS_SCRAMBLED_ZIPFIAN_GENERATOR_H_
