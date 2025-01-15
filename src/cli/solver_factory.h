#ifndef SOLVER_FACTORY_H
#define SOLVER_FACTORY_H

#include <array>
#include <memory>

#include "day_solver.h"
#include "problems/2024/year2024_day01.h"
#include "problems/2024/year2024_day02.h"
#include "problems/2024/year2024_day03.h"
#include "problems/2024/year2024_day04.h"

namespace adventofcode {
    inline constexpr std::array<int, 4> available_days = {
        202401, 202402, 202403, 202404, 
    };

    inline std::unique_ptr<DaySolver> createSolver(int yearday) {
        switch (yearday) {
            case 202401: return std::make_unique<Year2024Day01>();
            case 202402: return std::make_unique<Year2024Day02>();
            case 202403: return std::make_unique<Year2024Day03>();
            case 202404: return std::make_unique<Year2024Day04>();

            default: return nullptr;
        }
    }
}

#endif
