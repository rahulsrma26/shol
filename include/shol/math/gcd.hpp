#pragma once

#include <type_traits>

namespace shol {

template <class T>
typename std::enable_if<std::is_unsigned<T>::value, T>::type GCD(T u, T v) {
    int shift;
    if (u == 0)
        return v;
    if (v == 0)
        return u;

    for (shift = 0; ((u | v) & 1) == 0; ++shift) {
        u >>= 1;
        v >>= 1;
    }

    while ((u & 1) == 0)
        u >>= 1;

    do {
        while ((v & 1) == 0)
            v >>= 1;
        if (u > v) {
            T t = v;
            v = u;
            u = t;
        }
        v = v - u;
    } while (v != 0);

    return u << shift;
}

} // namespace shol
