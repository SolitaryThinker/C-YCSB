#ifndef GENERATOR_H_
#define GENERATOR_H_

namespace ycsbc {

template <typename Value>
class Generator {
    public:
        virtual Value Next() = 0;
        virtual Value Last() = 0;
        virtual ~Generator() { }
};

} // cycsb

#endif // GENERATOR_H_
