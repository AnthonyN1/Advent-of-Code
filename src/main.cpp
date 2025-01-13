#include <cstdlib>
#include <iostream>
#include <optional>
#include <string_view>
#include <vector>

#include "cli/args_parser.h"
#include "cli/utils.h"

inline static void printUsage() {
    std::cout << "Usage: ./adventofcode --help\n";
    std::cout << "       ./adventofcode --year <year> --alldays\n";
    std::cout << "       ./adventofcode --year <year> --day <day>\n";
    std::cout << "       ./adventofcode --year <year> --day <day> --part <1|2>";
    std::cout << std::endl;
}

int main(int argc, char **argv) {
    using namespace adventofcode;

    const std::vector<std::string_view> args(argv, argv + argc);

    if (cli::argsparser::hasOption(args, "--help")) {
        printUsage();
        return EXIT_SUCCESS;
    }

    if (!cli::argsparser::hasOption(args, "--year")) {
        printUsage();
        return EXIT_FAILURE;
    }

    auto year_str = cli::argsparser::getOption(args, "--year");
    auto year = cli::utils::getYear(year_str);
    if (!year) {
        printUsage();
        return EXIT_FAILURE;
    }

    if (cli::argsparser::hasOption(args, "--alldays")) {
        for (int day = 1; day <= 25; ++day) {
            cli::utils::solveDay(*year, day, std::nullopt);
        }
    } else if (cli::argsparser::hasOption(args, "--day")) {
        auto day_str = cli::argsparser::getOption(args, "--day");
        auto day = cli::utils::getDay(day_str);
        if (!day) {
            printUsage();
            return EXIT_FAILURE;
        }

        if (cli::argsparser::hasOption(args, "--part")) {
            auto part_str = cli::argsparser::getOption(args, "--part");
            cli::utils::solveDay(*year, *day, cli::utils::getPart(part_str));
        } else {
            cli::utils::solveDay(*year, *day, std::nullopt);
        }
    } else {
        printUsage();
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
