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
    std::vector<std::string> findUncorruptedInstructions(const std::string &instructions) {
        std::regex pattern(R"(mul\(\d{1,3},\d{1,3}\))");
        auto begin = std::sregex_iterator(instructions.cbegin(), instructions.cend(), pattern);
        auto end = std::sregex_iterator();

        auto match_to_str = [](const std::smatch &match) { return match.str(); };

        std::vector<std::string> uncorrupted;
        std::ranges::transform(std::ranges::subrange(begin, end), std::back_inserter(uncorrupted), match_to_str);

        return uncorrupted;
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

    std::string removeDisabledInstructions(const std::string &instructions) {
        std::regex pattern_newline(R"(\n)");
        std::string instructions_oneline = std::regex_replace(instructions, pattern_newline, "");

        std::regex pattern_disabled(R"(don't\(\).*?(?:do\(\)|$))");
        return std::regex_replace(instructions_oneline, pattern_disabled, "");
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
        auto enabled_instructions = removeDisabledInstructions(input_data);
        auto instructions = findUncorruptedInstructions(enabled_instructions);
        auto total = sumInstructions(instructions);

        return total;
    }
}
