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

namespace cycsb {

template <typename T>
void DiscreteGenerator<T>::AddValue(T value, double weight) {
  values_.push_back(std::make_pair(value, weight));
  sum_ += weight;
}

}  // namespace cycsb
