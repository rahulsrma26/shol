#pragma once

#include <ostream>
#include <tuple>

namespace shol {

// --------------------[ pair ]--------------------
template <class Ch, class Tr, class T1, class T2>
decltype(auto) operator<<(std::basic_ostream<Ch, Tr>& os,
                          const std::pair<T1, T2>& val) {
    return os << '(' << val.first << ',' << ' ' << val.second << ')';
}

// --------------------[ tuple ]--------------------
template <class Ch, class Tr, class Tuple, std::size_t... Is>
void print_tuple(std::basic_ostream<Ch, Tr>& os, Tuple const& t,
                 std::index_sequence<Is...>) {
    using swallow = int[];
    (void)swallow{0,
                  (void(os << (Is == 0 ? "" : ", ") << std::get<Is>(t)), 0)...};
}

template <class Ch, class Tr, class... Args>
decltype(auto) operator<<(std::basic_ostream<Ch, Tr>& os,
                          std::tuple<Args...> const& t) {
    os << '(';
    print_tuple(os, t, std::make_index_sequence<sizeof...(Args)>());
    return os << ')';
}

// --------------------[ container ]--------------------
// credits for is_container<> (https://gist.github.com/louisdx/1076849)

template <typename T>
struct has_const_iterator {
  private:
    typedef char one;
    typedef struct {
        char array[2];
    } two;

    template <typename C>
    static one test(typename C::const_iterator*);
    template <typename C>
    static two test(...);

  public:
    static const bool value = sizeof(test<T>(0)) == sizeof(one);
    typedef T type;
};

template <typename T>
struct has_begin_end {
    struct Dummy {
        typedef void const_iterator;
    };
    typedef
        typename std::conditional<has_const_iterator<T>::value, T, Dummy>::type
            TType;
    typedef typename TType::const_iterator iter;

    struct Fallback {
        iter begin() const;
        iter end() const;
    };
    struct Derived : TType, Fallback {};

    template <typename C, C>
    struct ChT;

    template <typename C>
    static char (&f(ChT<iter (Fallback::*)() const, &C::begin>*))[1];
    template <typename C>
    static char (&f(...))[2];
    template <typename C>
    static char (&g(ChT<iter (Fallback::*)() const, &C::end>*))[1];
    template <typename C>
    static char (&g(...))[2];

    static bool const beg_value = sizeof(f<Derived>(0)) == 2;
    static bool const end_value = sizeof(g<Derived>(0)) == 2;
};

template <typename T>
struct is_container {
    static const bool value = has_const_iterator<T>::value &&
                              has_begin_end<T>::beg_value &&
                              has_begin_end<T>::end_value;
};

template <class Ch, class Tr, class T>
typename std::enable_if<is_container<T>::value,
                        std::basic_ostream<Ch, Tr>&>::type
operator<<(std::basic_ostream<Ch, Tr>& os, const T& container) {
    os << '{';

    auto start = std::begin(container), end = std::end(container);
    if (start != end) {
        os << *start;
        for (start = std::next(start); start != end; start = std::next(start))
            os << ", " << *start;
    }

    return os << '}';
}

} // namespace shol
