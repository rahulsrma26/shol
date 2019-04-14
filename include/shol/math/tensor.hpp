#pragma once

#include <vector>
#include <memory>
#include <algorithm>
#include <functional>
#include <ostream>

namespace shol {

constexpr size_t LOW_DIM_PRINT_LIMIT = 12;
constexpr size_t LOW_DIM_PRINT_ELLIPSES = 4;
static_assert(
    LOW_DIM_PRINT_LIMIT > LOW_DIM_PRINT_ELLIPSES * 2,
    "Full element limit should be more than twice of ellipses element limit to prevent overflow.");

constexpr size_t HIGH_DIM_PRINT_LIMIT = 5;
constexpr size_t HIGH_DIM_PRINT_ELLIPSES = 2;
static_assert(
    HIGH_DIM_PRINT_LIMIT > HIGH_DIM_PRINT_ELLIPSES * 2,
    "Full element limit should be more than twice of ellipses element limit to prevent overflow.");

constexpr char PRINT_BEGIN = '[';
constexpr char PRINT_END = ']';

typedef uint16_t shapeType;
typedef std::vector<shapeType> shape;

template <class T>
class tensor {
    std::vector<T> data_m;
    shape dim_m{1};
    uint32_t size_m{};

    template <class Ch, class Tr>
    void print(std::basic_ostream<Ch, Tr>&, const shapeType, const size_t) const;

public:
    tensor() noexcept;
    tensor(const shape&);
    tensor(shape&&) noexcept;
    tensor(const tensor<T>&);
    tensor(tensor<T>&&) noexcept;

    tensor<T>& operator=(const tensor<T>&);
    tensor<T>& operator=(tensor<T>&&) noexcept;

    size_t size() const;
    void fill(const T& val);

    template <typename Function>
    void apply(Function generator);

    T& operator[](const shape&);
    const T& operator[](const shape&) const;

    template <class Ch, class Tr, class U>
    friend std::basic_ostream<Ch, Tr>& operator<<(std::basic_ostream<Ch, Tr>& os,
                                                  const tensor<U>& t);

    const shape& get_shape() const;
};

template <class Ch, class Tr>
std::basic_ostream<Ch, Tr>& operator<<(std::basic_ostream<Ch, Tr>&, const shape&);

// -------------------------------------------------------------------------------

template <class T>
tensor<T>::tensor() noexcept {}

template <class T>
tensor<T>::tensor(const shape& dim) : dim_m(dim), size_m(1) {
    for (const auto& x : dim_m)
        size_m *= x;
    data_m.resize(size_m);
}

template <class T>
tensor<T>::tensor(shape&& dim) noexcept : dim_m(std::move(dim)), size_m(1) {
    for (const auto& x : dim_m)
        size_m *= x;
    data_m.resize(size_m);
}

template <typename T>
tensor<T>::tensor(const tensor<T>& other)
    : dim_m(other.dim_m), size_m(other.size_m), data_m(other.data_m) {}

template <typename T>
tensor<T>::tensor(tensor<T>&& other) noexcept
    : dim_m(std::move(other.dim_m)), size_m(other.size_m), data_m(std::move(other.data_m)) {}

template <typename T>
tensor<T>& tensor<T>::operator=(const tensor<T>& other) {
    size_m = other.size_m;
    dim_m = other.dim_m;
    data_m = other.data_m;
    return *this;
}

template <typename T>
tensor<T>& tensor<T>::operator=(tensor<T>&& other) noexcept {
    size_m = other.size_m;
    dim_m = std::move(other.dim_m);
    data_m = std::move(other.data_m);
    return *this;
}

template <typename T>
size_t tensor<T>::size() const {
    return data_m.size();
}

template <typename T>
void tensor<T>::fill(const T& val) {
    std::fill(data_m.begin(), data_m.end(), val);
}

template <typename T>
template <typename Function>
void tensor<T>::apply(Function generator) {
    for (auto& element : data_m)
        element = generator(element);
}

template <typename T>
T& tensor<T>::operator[](const shape& idx) {
    size_t index = idx.back();
    for (size_t i = idx.size() - 1; i; i--)
        index = index * dim_m[i] + idx[i - 1];
    return data_m[index];
}

template <typename T>
const T& tensor<T>::operator[](const shape& idx) const {
    size_t index = idx.back();
    for (size_t i = idx.size() - 1; i; i--)
        index = index * dim_m[i] + idx[i - 1];
    return data_m[index];
}

template <typename T>
const shape& tensor<T>::get_shape() const {
    return dim_m;
}

template <typename T>
template <class Ch, class Tr>
void tensor<T>::print(std::basic_ostream<Ch, Tr>& os, const shapeType dim, const size_t idx) const {
    const auto n = dim_m[dim - 1];
    os << PRINT_BEGIN;
    if (dim == dim_m.size()) {
        if (n <= LOW_DIM_PRINT_LIMIT) {
            for (size_t i = idx; i < idx + n; i++)
                os << (i == idx ? "" : " ") << data_m[i];
        } else {
            for (size_t i = idx; i < idx + LOW_DIM_PRINT_ELLIPSES; i++)
                os << (i == idx ? "" : " ") << data_m[i];
            os << " ...";
            for (size_t i = idx + n - LOW_DIM_PRINT_ELLIPSES; i < idx + n; i++)
                os << ' ' << data_m[i];
        }
    } else {
        std::string spaces(dim, ' ');
        size_t inc = 1;
        for (shapeType i = dim; i < dim_m.size(); i++)
            inc *= dim_m[i];
        if (n <= HIGH_DIM_PRINT_LIMIT) {
            for (size_t i = idx, j = 0; j < n; i += inc, j++) {
                if (j)
                    os << spaces;
                print(os, dim + 1, i);
                if (j != n - 1)
                    os << '\n';
            }
        } else {
            for (size_t i = idx, j = 0; j < HIGH_DIM_PRINT_ELLIPSES; j++, i += inc) {
                if (j)
                    os << spaces;
                print(os, dim + 1, i);
                os << '\n';
            }
            os << spaces << "..." << '\n';
            for (size_t i = idx + (n - HIGH_DIM_PRINT_ELLIPSES) * inc, j = 0;
                 j < HIGH_DIM_PRINT_ELLIPSES; i += inc, j++) {
                os << spaces;
                print(os, dim + 1, i);
                if (j != HIGH_DIM_PRINT_ELLIPSES - 1)
                    os << '\n';
            }
        }
    }
    os << PRINT_END;
}

template <class Ch, class Tr, class U>
std::basic_ostream<Ch, Tr>& operator<<(std::basic_ostream<Ch, Tr>& os, const tensor<U>& t) {
    if (!t.dim_m.size())
        os << PRINT_BEGIN << PRINT_END;
    else
        t.print(os, 1, 0);
    return os;
}

template <class Ch, class Tr>
std::basic_ostream<Ch, Tr>& operator<<(std::basic_ostream<Ch, Tr>& os, const shape& s) {
    os << '(';
    for (size_t i = 0; i < s.size(); i++)
        os << (i ? " " : "") << s[i];
    return os << ')';
}

} // namespace shol