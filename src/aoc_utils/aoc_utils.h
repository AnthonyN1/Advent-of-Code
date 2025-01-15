#ifndef AOC_UTILS_H
#define AOC_UTILS_H

#include <unordered_map>
#include <vector>

namespace aocutils {
    template <class T> using Vec2D = std::vector<std::vector<T>>;

    template <class Container>
    std::unordered_map<typename Container::value_type, size_t> createFrequencyMap(const Container &elems) {
        std::unordered_map<typename Container::value_type, size_t> freqs;
        for (const auto &elem : elems) {
            ++freqs[elem];
        }
        return freqs;
    }

    template <class Numeric> int sgn(const Numeric &num) {
        if (num > static_cast<Numeric>(0)) {
            return 1;
        } else if (num < static_cast<Numeric>(0)) {
            return -1;
        } else {
            return 0;
        }
    }
}

#endif
