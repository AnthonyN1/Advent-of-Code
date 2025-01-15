#ifndef YEAR2024_DAY04_H
#define YEAR2024_DAY04_H

#include "day_solver.h"

namespace adventofcode {
    class Year2024Day04 final : public DaySolver {
    public:
        Year2024Day04();
        ~Year2024Day04() override = default;

        ResultType solvePart1() override;
        ResultType solvePart2() override;
    };
}

#endif
