#ifndef CONST_GENERATOR_H_
#define CONST_GENERATOR_H_

#include "generator.h"
#include <cstdint>

namespace ycsbc {

class ConstGenerator : public Generator<uint64_t> {
    public:
        ConstGenerator(int constant) : constant_(constant) { }
        uint64_t Next() { return constant_; }
        uint64_t Last() { return constant_; }
    private:
        uint64_t constant_;
};

} // ycsbc

#endif // CONST_GENERATOR_H_
