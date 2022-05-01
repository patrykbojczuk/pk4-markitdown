#ifndef NTHELEMENT_H
#define NTHELEMENT_H

#include <cstddef>

template <typename T>
class NthElement {
public:
    NthElement(size_t n, T value);

    bool operator()(T c);
private:
    size_t n;
    T value;
};

#endif //NTHELEMENT_H
