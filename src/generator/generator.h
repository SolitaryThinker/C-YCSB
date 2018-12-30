#ifndef CYCSB_GENERATOR_GENERATOR_H_
#define CYCSB_GENERATOR_GENERATOR_H_

namespace cycsb {

template <typename Value>
class Generator {
    public:
        virtual Value Next() = 0;
        virtual Value Last() = 0;
        virtual ~Generator() { }
};

}  // cycsb

#endif  // CYCSB_GENERATOR_GENERATOR_H_
