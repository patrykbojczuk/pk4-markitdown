#ifndef NTHELEMENT_HPP
#define NTHELEMENT_HPP

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

template<typename T>
NthElement<T>::NthElement(size_t n, T value): n(n), value(value) {}

template<typename T>
bool NthElement<T>::operator()(T c) {
    return c == value && !--n;
}

#endif //NTHELEMENT_HPP
