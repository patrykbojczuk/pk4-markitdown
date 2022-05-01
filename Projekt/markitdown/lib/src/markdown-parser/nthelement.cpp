#include "nthelement.h"

template<typename T>
NthElement<T>::NthElement(size_t n, T value): n(n), value(value) {}

template<typename T>
bool NthElement<T>::operator()(T c) {
    return c == value && !--n;
}
