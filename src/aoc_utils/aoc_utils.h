#ifndef AOC_UTILS_H
#define AOC_UTILS_H

#include <unordered_map>

namespace adventofcode::aocutils {
    template <class Container>
    std::unordered_map<typename Container::value_type, size_t> createFrequencyMap(const Container &elems) {
        std::unordered_map<typename Container::value_type, size_t> freqs;
        for (const auto &elem : elems) {
            ++freqs[elem];
        }
        return freqs;
    }
}

#endif
