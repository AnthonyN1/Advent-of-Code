#include <algorithm>
#include <array>
#include <cstddef>
#include <sstream>
#include <string>
#include <utility>

#include "aoc_utils/aoc_utils.h"
#include "year2024_day04.h"

namespace {
    aocutils::Vec2D<char> transformInput(const std::string &input) {
        aocutils::Vec2D<char> word_search;

        std::istringstream ss{input};
        std::string line;
        while (std::getline(ss, line)) {
            word_search.push_back({line.begin(), line.end()});
        }

        return word_search;
    }

    long countXmasAtX(const aocutils::Vec2D<char> &word_search, size_t r, size_t c) {
        constexpr std::array<std::pair<int, int>, 8> directions = {
            {{0, 1}, {0, -1}, {-1, 0}, {1, 0}, {-1, 1}, {-1, -1}, {1, -1}, {1, 1}}};

        auto count_in_direction = [&](const std::pair<int, int> &direction) {
            if (!aocutils::areIndicesInBounds(word_search, {r + 3 * direction.first, c + 3 * direction.second}))
                return false;

            std::string word{'X'};
            for (int i = 1; i <= 3; ++i) {
                word += word_search[r + i * direction.first][c + i * direction.second];
            }

            return word == "XMAS";
        };

        return std::ranges::count_if(directions, count_in_direction);
    }

    long countXmas(const aocutils::Vec2D<char> &word_search) {
        auto counter = 0;
        for (size_t r = 0; r < word_search.size(); ++r)
            for (size_t c = 0; c < word_search[r].size(); ++c)
                if (word_search[r][c] == 'X')
                    counter += countXmasAtX(word_search, r, c);

        return counter;
    }

    bool isTwoMas(const aocutils::Vec2D<char> &word_search, size_t r, size_t c) {
        constexpr std::array<std::pair<int, int>, 2> directions = {{{1, -1}, {-1, -1}}};

        auto check_mas = [&](const std::pair<int, int> &dir) {
            auto char1 = word_search[r + dir.first][c + dir.second];
            auto char2 = word_search[r - dir.first][c - dir.second];

            return (char1 == 'M' && char2 == 'S') || (char1 == 'S' && char2 == 'M');
        };

        return check_mas(directions[0]) && check_mas(directions[1]);
    }

    long countTwoMas(const aocutils::Vec2D<char> &word_search) {
        auto counter = 0;
        for (size_t r = 1; r < word_search.size() - 1; ++r)
            for (size_t c = 1; c < word_search[r].size() - 1; ++c)
                if (word_search[r][c] == 'A' && isTwoMas(word_search, r, c))
                    ++counter;

        return counter;
    }
}

namespace adventofcode {
    Year2024Day04::Year2024Day04() : DaySolver(2024, 4) {}

    ResultType Year2024Day04::solvePart1() {
        auto word_search = transformInput(input_data);
        auto total = countXmas(word_search);

        return total;
    }

    ResultType Year2024Day04::solvePart2() {
        auto word_search = transformInput(input_data);
        auto total = countTwoMas(word_search);

        return total;
    }
}
