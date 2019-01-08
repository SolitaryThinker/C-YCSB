//
//  const_generator.h
//  CYCSB
//
//  Created by Jinglei Ren on 12/9/14.
//  Modified by William Lin
//  Copyright (c) 2014 Jinglei Ren <jinglei@ren.systems>.
//

#ifndef CYCSB_GENERATOR_CONST_GENERATOR_H_
#define CYCSB_GENERATOR_CONST_GENERATOR_H_

#include "generator.h"
#include <cstdint>

namespace cycsb {

class ConstGenerator : public Generator<uint64_t> {
    public:
        ConstGenerator(int constant) : constant_(constant) { }
        uint64_t NextValue() override { return constant_; }
        uint64_t LastValue() override { return constant_; }
    private:
        uint64_t constant_;
};

}  // cycsb

#endif  // CYCSB_GENERATOR_CONST_GENERATOR_H_
