#ifndef SOLVER_FACTORY_H
#define SOLVER_FACTORY_H

#include <array>
#include <memory>

#include "../day_solver.h"
#include "../problems/2024/year2024_day01.h"
#include "../problems/2024/year2024_day02.h"

namespace adventofcode {
    inline constexpr std::array<int, 2> available_days = {
        202401, 202402, 
    };

    inline std::unique_ptr<DaySolver> createSolver(int yearday) {
        switch (yearday) {
            case 202401: return std::make_unique<Year2024Day01>();
case 202402: return std::make_unique<Year2024Day02>();

            default: return nullptr;
        }
    }
}

#endif
