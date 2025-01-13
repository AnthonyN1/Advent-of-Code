#ifndef RESULT_H
#define RESULT_H

#include <ostream>
#include <variant>

template <class T> struct Streamer {
    const T &val;
};
template <class T> Streamer(T) -> Streamer<T>;

template <class T> std::ostream &operator<<(std::ostream &os, Streamer<T> s) {
    os << s.val;
    return os;
}

template <class... Ts> std::ostream &operator<<(std::ostream &os, Streamer<std::variant<Ts...>> sv) {
    std::visit([&os](const auto &v) { os << Streamer{v}; }, sv.val);
    return os;
}

#endif
