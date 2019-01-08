//
//  uniform_generator.h
//  YCSB-C
//
//  Created by Jinglei Ren on 12/6/14.
//  Modified by William Lin
//  Copyright (c) 2014 Jinglei Ren <jinglei@ren.systems>.
//

#ifndef CYCSB_GENERATOR_UNIFORM_GENERATOR_H_
#define CYCSB_GENERATOR_UNIFORM_GENERATOR_H_

#include <cstdint>
#include <mutex>
#include <random>

#include "generator/generator.h"

namespace cycsb {

class UniformGenerator : public Generator<uint64_t> {
  public:
  // Both min and max are inclusive
  UniformGenerator(uint64_t min, uint64_t max) : distribution_(min, max) {
    NextValue();
  }

  uint64_t NextValue() override;
  uint64_t LastValue() override;

 private:
  std::mt19937_64 generator_;
  std::uniform_int_distribution<uint64_t> distribution_;
  uint64_t last_int_;
  std::mutex mutex_;
};

inline uint64_t UniformGenerator::NextValue() {
  std::lock_guard<std::mutex> lock(mutex_);
  return last_int_ = distribution_(generator_);
}

inline uint64_t UniformGenerator::LastValue() {
  std::lock_guard<std::mutex> lock(mutex_);
  return last_int_;
}

}  // namespace cycsb

#endif  // CYCSB_GENERATOR_UNIFORM_GENERATOR_H_
