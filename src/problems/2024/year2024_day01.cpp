#include <algorithm>
#include <cstdlib>
#include <numeric>
#include <sstream>
#include <string>
#include <string_view>
#include <tuple>
#include <unordered_map>
#include <vector>

#include "year2024_day01.h"

namespace {
    std::tuple<std::vector<long>, std::vector<long>> transformInput(std::string_view input) {
        std::vector<long> left, right;

        std::istringstream ss{std::string(input)};
        long curr_left, curr_right;
        while (ss >> curr_left >> curr_right) {
            left.push_back(curr_left);
            right.push_back(curr_right);
        }

        return {left, right};
    }

    void sortLists(std::vector<long> &l1, std::vector<long> &l2) {
        std::ranges::sort(l1);
        std::ranges::sort(l2);
    }

    long calcTotalDistance(const std::vector<long> &left, const std::vector<long> &right) {
        std::vector<long> distances(left.size());
        std::transform(left.cbegin(), left.cend(), right.cbegin(), distances.begin(),
                       [](long n1, long n2) { return std::abs(n1 - n2); });
        auto total = std::accumulate(distances.cbegin(), distances.cend(), 0L);

        return total;
    }

    std::unordered_map<long, size_t> createFrequencyMap(const std::vector<long> &elems) {
        std::unordered_map<long, size_t> freqs;
        for (auto elem : elems) {
            ++freqs[elem];
        }
        return freqs;
    }

    long calcTotalSimilarityScore(const std::vector<long> &left, const std::unordered_map<long, size_t> &freqs) {
        auto addSimilarityScore = [&](long running, long elem) {
            auto score = running;
            if (freqs.contains(elem)) {
                score += elem * freqs.at(elem);
            }
            return score;
        };

        auto total = std::accumulate(left.cbegin(), left.cend(), 0L, addSimilarityScore);

        return total;
    }
}

namespace adventofcode {
    Year2024Day01::Year2024Day01() : DaySolver(2024, 1) {}

    ResultType Year2024Day01::solvePart1() {
        auto [left, right] = transformInput(input_data);
        sortLists(left, right);
        auto totalDistance = calcTotalDistance(left, right);

        return totalDistance;
    }

    ResultType Year2024Day01::solvePart2() {
        auto [left, right] = transformInput(input_data);
        auto freqs = createFrequencyMap(right);
        auto totalScore = calcTotalSimilarityScore(left, freqs);

        return totalScore;
    }
}