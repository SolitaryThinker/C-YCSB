#ifndef CYCSB_GENERATOR_GENERATOR_H_
#define CYCSB_GENERATOR_GENERATOR_H_

namespace cycsb {

template <typename T>
class Generator {
    public:
        virtual T NextValue() = 0;
        virtual T LastValue() = 0;
        virtual ~Generator() { }
};

}  // cycsb

#endif  // CYCSB_GENERATOR_GENERATOR_H_
