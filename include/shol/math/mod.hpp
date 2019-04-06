#pragma once

#include <type_traits>
#include <ostream>

namespace shol {

template <class T, T Modulus>
class Modular {
    static_assert(Modulus >= 2, "Modular arithmatic for base less than 2 is not supported");

private:
    T value;

public:
    Modular(const T& init);
    Modular(const Modular& other);
    Modular& operator=(const Modular& other);
    Modular operator-() const;
    T Value() const;

    Modular& operator+=(const Modular& a);
    Modular& operator-=(const Modular& a);
    Modular& operator*=(const Modular& a);
    Modular& operator/=(const Modular& a);

    template <class T1, T1 Modulus1>
    friend Modular<T1, Modulus1> operator+(const Modular<T1, Modulus1>& a,
                                           const Modular<T1, Modulus1>& b);

    template <class T1, T1 Modulus1>
    friend Modular<T1, Modulus1> operator-(const Modular<T1, Modulus1>& a,
                                           const Modular<T1, Modulus1>& b);

    template <class T1, T1 Modulus1>
    friend Modular<T1, Modulus1> operator*(const Modular<T1, Modulus1>& a,
                                           const Modular<T1, Modulus1>& b);

    template <class T1, T1 Modulus1>
    friend Modular<T1, Modulus1> operator/(const Modular<T1, Modulus1>& a,
                                           const Modular<T1, Modulus1>& b);

    template <class T1, T1 Modulus1>
    friend Modular<T1, Modulus1> pow(Modular<T1, Modulus1> i, T1 j);
    template <class T1, T1 Modulus1>
    friend Modular<T1, Modulus1> inv(Modular<T1, Modulus1> i);
};

template <class T, T Modulus>
Modular<T, Modulus>::Modular(const T& init) : value(init % Modulus) {
    if (value < 0)
        value += Modulus;
}

template <class T, T Modulus>
Modular<T, Modulus>::Modular(const Modular& other) : value(other.value) {}

template <class T, T Modulus>
Modular<T, Modulus>& Modular<T, Modulus>::operator=(const Modular<T, Modulus>& other) {
    value = other.value;
    return *this;
}

template <class T, T Modulus>
Modular<T, Modulus> Modular<T, Modulus>::operator-() const {
    if (value)
        return Modular(Modulus - value);
    return Modular(0);
}

template <class T, T Modulus>
Modular<T, Modulus>& Modular<T, Modulus>::operator+=(const Modular<T, Modulus>& a) {
    value += a.value;
    if (value >= Modulus)
        value -= Modulus;
    return *this;
}

template <class T, T Modulus>
Modular<T, Modulus>& Modular<T, Modulus>::operator-=(const Modular<T, Modulus>& a) {
    value += Modulus - a.value;
    if (value >= Modulus)
        value -= Modulus;
    return *this;
}

template <class T, T Modulus>
Modular<T, Modulus>& Modular<T, Modulus>::operator*=(const Modular<T, Modulus>& a) {
    value *= a.value;
    if (value >= Modulus)
        value %= Modulus;
    return *this;
}

template <class T, T Modulus>
Modular<T, Modulus>& Modular<T, Modulus>::operator/=(const Modular<T, Modulus>& a) {
    *this *= inv(a);
    if (value >= Modulus)
        value %= Modulus;
    return *this;
}

template <class T, T Modulus>
T Modular<T, Modulus>::Value() const {
    return value;
}

template <class T, T Modulus>
Modular<T, Modulus> operator+(const Modular<T, Modulus>& a, const Modular<T, Modulus>& b) {
    Modular<T, Modulus> s(a.value);
    return s += b;
}

template <class T, T Modulus>
Modular<T, Modulus> operator-(const Modular<T, Modulus>& a, const Modular<T, Modulus>& b) {
    Modular<T, Modulus> s(a.value);
    return s -= b;
}

template <class T, T Modulus>
Modular<T, Modulus> operator*(const Modular<T, Modulus>& a, const Modular<T, Modulus>& b) {
    Modular<T, Modulus> s(a.value);
    return s *= b;
}

template <class T, T Modulus>
Modular<T, Modulus> operator/(const Modular<T, Modulus>& a, const Modular<T, Modulus>& b) {
    Modular<T, Modulus> s(a.value);
    return s /= b;
}

template <class T, T Modulus>
Modular<T, Modulus> pow(const Modular<T, Modulus> i, T j) {
    if (j == T(0))
        return Modular<T, Modulus>(1);

    if (i.value < T(2))
        return i;

    Modular<T, Modulus> p(1), v(i);
    while (j) {
        if (j & 1)
            p *= v;
        v *= v;
        j >>= 1;
    }
    return p;
}

template <class T, T Modulus>
Modular<T, Modulus> inv(const Modular<T, Modulus> i) {
    return pow<T, Modulus>(i, Modulus - 2);
}

template <class Ch, class Tr, class T, T Modulus>
decltype(auto) operator<<(std::basic_ostream<Ch, Tr>& os, const Modular<T, Modulus> i) {
    return os << i.Value();
}

} // namespace shol
