//
//  discrete_generator.h
//  CYCSB
//
//  Created by Jinglei Ren on 12/6/14.
//  Modified by William Lin
//  Copyright (c) 2014 Jinglei Ren <jinglei@ren.systems>.
//

#ifndef CYCSB_GENERATOR_DISCRETE_GENERATOR_H_
#define CYCSB_GENERATOR_DISCRETE_GENERATOR_H_

#include <atomic>
#include <cassert>
#include <mutex>
#include <string>
#include <vector>

#include "generator/generator.h"
#include "util/utils.h"

namespace cycsb {

template <typename T>
class DiscreteGenerator : public Generator<T> {
  public:
    DiscreteGenerator() : sum_(0) { }
    void AddValue(T value, double weight);

    T NextValue() override;

    T LastValue() override {
      if (values_.empty()) {
        last_ = NextValue();
      }
      return last_;
    }

  protected:
    std::vector<std::pair<T, double>> values_;
    double sum_;
    std::atomic<T> last_;
    std::mutex mutex_;
};

template <typename T>
void DiscreteGenerator<T>::AddValue(T value, double weight) {
  values_.push_back(std::make_pair(value, weight));
  sum_ += weight;
}

template <typename T>
T DiscreteGenerator<T>::NextValue() {
  mutex_.lock();
  double chooser = utils::RandomDouble();
  mutex_.unlock();

  for (auto p = values_.cbegin(); p != values_.cend(); ++p) {
    if (chooser < p->second / sum_) {
      return last_ = p->first;
    }
    chooser -= p->second / sum_;
  }

  assert(false);
}

}  // namespace cycsb

#endif  // CYCSB_GENERATOR_DISCRETE_GENERATOR_H_
