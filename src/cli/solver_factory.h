#ifndef SOLVER_FACTORY_H
#define SOLVER_FACTORY_H

#include <array>
#include <memory>

#include "../day_solver.h"
#include "../problems/2024/year2024_day01.h"

namespace adventofcode {
    inline constexpr std::array<int, 1> available_days = {
        202401, 
    };

    inline std::unique_ptr<DaySolver> createSolver(int yearday) {
        switch (yearday) {
            case 202401: return std::make_unique<Year2024Day01>();

            default: return nullptr;
        }
    }
}

#endif
