#ifndef ARGS_PARSER_H
#define ARGS_PARSER_H

#include <ranges>
#include <string_view>
#include <vector>

namespace adventofcode::cli::argsparser {
    inline std::string_view getOption(const std::vector<std::string_view> &args, std::string_view option_name) {
        if (const auto it = std::ranges::find(args, option_name); it != args.end()) {
            return *(it + 1);
        }
        return "";
    }

    inline bool hasOption(const std::vector<std::string_view> &args, std::string_view option_name) {
        return std::ranges::find(args, option_name) != args.end();
    }
}

#endif
