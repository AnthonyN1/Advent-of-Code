#ifndef CLI_UTILS_H
#define CLI_UTILS_H

#include <algorithm>
#include <iostream>
#include <optional>
#include <string>
#include <string_view>

#include "result.h"
#include "solver_factory.h"

namespace adventofcode::cli::utils {
    inline std::optional<int> parseNumber(std::string_view str) {
        std::optional<int> number;
        try {
            number = std::stoi(std::string(str));
        } catch (...) {
            return std::nullopt;
        }
        return number;
    }

    inline std::optional<int> getYear(std::string_view year_str) {
        if (year_str.empty()) {
            std::cerr << "The year must be provided.\n";
            return std::nullopt;
        }

        auto year = parseNumber(year_str);
        if (!year || *year < 2015 || *year > 2024) {
            std::cerr << "The year must be between 2015 and 2024.\n";
            return std::nullopt;
        }
        return year;
    }

    inline std::optional<int> getDay(std::string_view day_str) {
        if (day_str.empty()) {
            std::cerr << "The day must be provided.\n";
            return std::nullopt;
        }

        auto day = parseNumber(day_str);
        if (!day || *day < 1 || *day > 25) {
            std::cerr << "The day must be between 1 and 25.\n";
            return std::nullopt;
        }
        return day;
    }

    inline std::optional<Part> getPart(std::string_view part_str) {
        if (part_str.empty()) {
            return std::nullopt;
        } else if (part_str == "1") {
            return Part::Part1;
        } else if (part_str == "2") {
            return Part::Part2;
        }

        std::cerr << "The part must be either 1 or 2\n";
        return std::nullopt;
    }

    inline void solveDay(int year, int day, std::optional<Part> part) {
        int yearday = year * 100 + day;

        if (!std::ranges::contains(available_days, yearday)) {
            std::cerr << "No solver found for year " << year << " day " << day << std::endl;
            return;
        }

        auto solve_part = [&](Part p) {
            std::cout << "- Part " << (p == Part::Part1 ? "1" : "2") << std::endl;
            const auto solver = createSolver(yearday);
            const auto [result, duration] = solver->timedSolve(p);
            std::cout << "  -> Result: " << Streamer{result} << " (in " << duration << " us)" << std::endl;
        };

        std::cout << "# Year " << year << " Day " << day << " running..." << std::endl;

        if (part) {
            solve_part(*part);
        } else {
            solve_part(Part::Part1);
            solve_part(Part::Part2);
        }
    }
}

#endif
