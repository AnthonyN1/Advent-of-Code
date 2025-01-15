#ifndef AOC_UTILS_H
#define AOC_UTILS_H

#include <cstddef>
#include <unordered_map>
#include <utility>
#include <vector>

namespace aocutils {
    template <class T> using Vec2D = std::vector<std::vector<T>>;

    template <class T> bool areIndicesInBounds(const Vec2D<T>& vec, const std::pair<int, int> &idxs) {
        auto [r, c] = idxs;
        return (r >= 0) && (r < static_cast<int>(vec.size())) && (c >= 0) && (c < static_cast<int>(vec[r].size()));
    }

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
