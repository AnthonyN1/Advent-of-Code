#ifndef YEAR2024_DAY03_H
#define YEAR2024_DAY03_H

#include "day_solver.h"

namespace adventofcode {
    class Year2024Day03 final : public DaySolver {
    public:
        Year2024Day03();
        ~Year2024Day03() override = default;

        ResultType solvePart1() override;
        ResultType solvePart2() override;
    };
}

#endif
