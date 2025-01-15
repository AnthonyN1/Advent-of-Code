#include <algorithm>
#include <functional>
#include <iterator>
#include <numeric>
#include <ranges>
#include <regex>
#include <string>
#include <vector>

#include "../../aoc_utils/aoc_utils.h"
#include "year2024_day03.h"

namespace {
    std::vector<std::string> findInstructions(const std::string &instructions, const char *pattern) {
        std::regex pattern_regex(pattern);
        auto begin = std::sregex_iterator(instructions.cbegin(), instructions.cend(), pattern_regex);
        auto end = std::sregex_iterator();

        auto match_to_str = [](const std::smatch &match) { return match.str(); };

        std::vector<std::string> uncorrupted;
        std::ranges::transform(std::ranges::subrange(begin, end), std::back_inserter(uncorrupted), match_to_str);

        return uncorrupted;
    }

    std::vector<std::string> findUncorruptedInstructions(const std::string &instructions) {
        return findInstructions(instructions, R"(mul\(\d{1,3},\d{1,3}\))");
    }

    std::vector<std::string> findEnabledUncorruptedInstructions(const std::string &instructions) {
        std::regex pattern_n(R"(\n)");
        std::string instructions_new = std::regex_replace(instructions, pattern_n, "");

        std::regex pattern(R"(don't\(\).*?(?:do\(\)|$))");
        std::string enabled_instructions = std::regex_replace(instructions_new, pattern, "");

        return findInstructions(enabled_instructions, R"(mul\(\d{1,3},\d{1,3}\))");
    }

    long sumInstructions(const std::vector<std::string> &instructions) {
        auto parse_mul = [](const std::string &instruction) {
            std::regex pattern(R"(\d{1,3})");
            auto begin = std::sregex_iterator(instruction.cbegin(), instruction.cend(), pattern);
            auto end = std::sregex_iterator();

            return std::transform_reduce(begin, end, 1L, std::multiplies{},
                                         [](const std::smatch &match) { return std::stoi(match.str()); });
        };

        return std::transform_reduce(instructions.cbegin(), instructions.cend(), 0L, std::plus{}, parse_mul);
    }
}

namespace adventofcode {
    Year2024Day03::Year2024Day03() : DaySolver(2024, 3) {}

    ResultType Year2024Day03::solvePart1() {
        auto instructions = findUncorruptedInstructions(input_data);
        auto total = sumInstructions(instructions);

        return total;
    }

    ResultType Year2024Day03::solvePart2() {
        auto instructions = findEnabledUncorruptedInstructions(input_data);
        auto total = sumInstructions(instructions);

        return total;
    }
}
