#ifndef CYCSB_GENERATOR_CONST_GENERATOR_H_
#define CYCSB_GENERATOR_CONST_GENERATOR_H_

#include "generator.h"
#include <cstdint>

namespace cycsb {

class ConstGenerator : public Generator<uint64_t> {
    public:
        ConstGenerator(int constant) : constant_(constant) { }
        uint64_t NextValue() { return constant_; }
        uint64_t LastValue() { return constant_; }
    private:
        uint64_t constant_;
};

}  // cycsb

#endif  // CYCSB_GENERATOR_CONST_GENERATOR_H_
