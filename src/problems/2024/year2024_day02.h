#ifndef YEAR2024_DAY02_H
#define YEAR2024_DAY02_H

#include "../../day_solver.h"

namespace adventofcode {
    class Year2024Day02 final : public DaySolver {
    public:
        Year2024Day02();
        ~Year2024Day02() override = default;

        ResultType solvePart1() override;
        ResultType solvePart2() override;
    };
}

#endif
