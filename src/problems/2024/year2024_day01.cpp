#include <algorithm>
#include <cmath>
#include <functional>
#include <numeric>
#include <ranges>
#include <sstream>
#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>

#include "aoc_utils/aoc_utils.h"
#include "year2024_day01.h"

namespace {
    std::tuple<std::vector<long>, std::vector<long>> transformInput(const std::string &input) {
        std::vector<long> left, right;

        std::istringstream ss{input};
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
        auto calc_distance = [&](int i) { return std::abs(left[i] - right[i]); };

        auto idxs = std::views::iota(0, std::ssize(left));
        return std::transform_reduce(idxs.cbegin(), idxs.cend(), 0L, std::plus{}, calc_distance);
    }

    long calcTotalSimilarityScore(const std::vector<long> &left, const std::unordered_map<long, size_t> &freqs) {
        auto calc_similarity_score = [&](long elem) { return freqs.contains(elem) ? elem * freqs.at(elem) : 0L; };

        return std::transform_reduce(left.cbegin(), left.cend(), 0L, std::plus{}, calc_similarity_score);
    }
}

namespace adventofcode {
    Year2024Day01::Year2024Day01() : DaySolver(2024, 1) {}

    ResultType Year2024Day01::solvePart1() {
        auto [left, right] = transformInput(input_data);
        sortLists(left, right);
        auto total_distance = calcTotalDistance(left, right);

        return total_distance;
    }

    ResultType Year2024Day01::solvePart2() {
        auto [left, right] = transformInput(input_data);
        auto freqs = aocutils::createFrequencyMap(right);
        auto total_score = calcTotalSimilarityScore(left, freqs);

        return total_score;
    }
}