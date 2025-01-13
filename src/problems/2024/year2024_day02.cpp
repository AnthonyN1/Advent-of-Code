#include <algorithm>
#include <list>
#include <numeric>
#include <ranges>
#include <sstream>
#include <string>
#include <vector>

#include "year2024_day02.h"

#include <iostream>

namespace {
    std::vector<std::vector<long>> transformInput(const std::string &input) {
        std::vector<std::vector<long>> reports;

        std::istringstream ss{input};
        std::string line;
        while (std::getline(ss, line)) {
            std::istringstream ss_line{line};
            long level;

            std::vector<long> levels;
            while (ss_line >> level) {
                levels.push_back(level);
            }

            reports.push_back(levels);
        }

        return reports;
    }

    bool isSafe(const std::vector<long> &report) {
        std::list<long> differences(report.size());
        std::adjacent_difference(report.cbegin(), report.cend(), differences.begin());
        differences.pop_front();

        auto is_positive = std::ranges::all_of(differences, [](long diff) { return diff > 0; });
        auto is_negative = std::ranges::all_of(differences, [](long diff) { return diff < 0; });
        auto is_in_bounds =
            std::ranges::all_of(differences, [](long diff) { return std::abs(diff) >= 1 && std::abs(diff) <= 3; });

        return (is_positive || is_negative) && is_in_bounds;
    }

    size_t countSafeReports(const std::vector<std::vector<long>> &reports) {
        return std::ranges::count_if(reports, isSafe);
    }

    size_t countSafeReportsWithTolerance(const std::vector<std::vector<long>> &reports) {
        auto is_safe_with_tol = [](const std::vector<long> &report) {
            std::vector<long> removed_level;
            removed_level.reserve(report.size() - 1);

            auto idxs = std::views::iota(0, std::ssize(report));
            return std::ranges::any_of(idxs, [&](int i) {
                removed_level.clear();
                removed_level.insert(removed_level.end(), report.cbegin(), report.cbegin() + i);
                removed_level.insert(removed_level.end(), report.cbegin() + i + 1, report.cend());

                return isSafe(removed_level);
            });
        };

        return std::ranges::count_if(reports, is_safe_with_tol);
    }
}

namespace adventofcode {
    Year2024Day02::Year2024Day02() : DaySolver(2024, 2) {}

    ResultType Year2024Day02::solvePart1() {
        auto reports = transformInput(input_data);
        auto num_safe = countSafeReports(reports);

        return num_safe;
    }

    ResultType Year2024Day02::solvePart2() {
        auto reports = transformInput(input_data);
        auto num_safe = countSafeReportsWithTolerance(reports);

        return num_safe;
    }
}
