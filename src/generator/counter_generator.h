//
//  counter_generator.h
//  CYCSB
//
//  Created by Jinglei Ren on 12/9/14.
//  Modified by William Lin
//  Copyright (c) 2014 Jinglei Ren <jinglei@ren.systems>.
//

#ifndef CYCSB_GENERATOR_COUNTER_GENERATOR_H_
#define CYCSB_GENERATOR_COUNTER_GENERATOR_H_

#include "generator/generator.h"

#include <cstdint>
#include <atomic>

namespace cycsb {

class CounterGenerator : public Generator<uint64_t> {
 public:
  CounterGenerator(uint64_t start) : counter_(start) { }
  uint64_t NextValue() override { return counter_.fetch_add(1); }
  uint64_t LastValue() override { return counter_.load() - 1; }
  void Set(uint64_t start) { counter_.store(start); }
 private:
  std::atomic<uint64_t> counter_;
};

}  // namespace cycsb

#endif // CYCSB_GENERATOR_COUNTER_GENERATOR_H_
