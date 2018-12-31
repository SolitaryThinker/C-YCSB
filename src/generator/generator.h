#ifndef CYCSB_GENERATOR_GENERATOR_H_
#define CYCSB_GENERATOR_GENERATOR_H_

namespace cycsb {

template <typename Value>
class Generator {
    public:
        virtual Value NextValue() = 0;
        virtual Value LastValue() = 0;
        virtual ~Generator() { }
};

}  // cycsb

#endif  // CYCSB_GENERATOR_GENERATOR_H_
