#ifndef DAY_SOLVER_H
#define DAY_SOLVER_H

#include <chrono>
#include <cstddef>
#include <fstream>
#include <iterator>
#include <string>
#include <variant>

#include "inputs.h"

namespace adventofcode {
    enum class Part { Part1, Part2 };
    using ResultType = std::variant<long, size_t, std::string>;

    struct DayResult {
        ResultType result;
        long long duration = 0;
    };

    class DaySolver {
    public:
        DaySolver() = delete;
        explicit DaySolver(size_t inYear, size_t inDay)
            : input_data{
                  std::istreambuf_iterator<char>(std::ifstream(std::string(inputs[inYear - 2015][inDay - 1])).rdbuf()),
                  std::istreambuf_iterator<char>()} {}
        virtual ~DaySolver() = default;

        virtual ResultType solvePart1() = 0;
        virtual ResultType solvePart2() = 0;

        DayResult timedSolve(Part part) {
            const auto start = std::chrono::high_resolution_clock::now();
            const auto result = part == Part::Part1 ? solvePart1() : solvePart2();
            const auto end = std::chrono::high_resolution_clock::now();
            return {result, std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()};
        }

    protected:
        std::string input_data;
    };
}

#endif
