#ifndef YEAR2024_DAY01_H
#define YEAR2024_DAY01_H

#include "../../day_solver.h"

namespace adventofcode {
    class Year2024Day01 final : public DaySolver {
    public:
        Year2024Day01();
        ~Year2024Day01() override = default;

        ResultType solvePart1() override;
        ResultType solvePart2() override;
    };
}

#endif
