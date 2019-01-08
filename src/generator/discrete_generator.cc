//
//  discrete_generator.cc
//  CYCSB
//
//  Created by Jinglei Ren on 12/6/14.
//  Modified by William Lin
//  Copyright (c) 2014 Jinglei Ren <jinglei@ren.systems>.
//

#include "generator/discrete_generator.h"

#include "util/utils.h"
#include <cassert>

namespace cycsb {

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
