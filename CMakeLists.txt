﻿# Usage: cmake --build build --target adventofcode

cmake_minimum_required(VERSION 3.20)
project(adventofcode
        VERSION 1.0.0
        DESCRIPTION "C++ solutions for Advent of Code"
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
if(MSVC)
    add_compile_options("/W4" "$<$<CONFIG:RELEASE>:/O2>")
else()
    set(CMAKE_CXX_FLAGS "-Wshadow -Wall -Wextra -Wfatal-errors -Wconversion -Wpedantic")
    set(CMAKE_CXX_FLAGS_DEBUG "-g")
    set(CMAKE_CXX_FLAGS_RELEASE "-O3")
endif()

# Handles inputs as filenames and automatically generates an inputs.h file.
set(INPUTS_CONTENT "")

# Iterates through each Advent of Code year.
foreach(YEAR_NUMBER RANGE 2015 2024)
    string(APPEND INPUTS_CONTENT "{")

    # Iterates through each day.
    foreach(DAY_NUMBER RANGE 1 25)
        # Potentially adds a leading zero to the day.
        set(DAY_FILENAME ${DAY_NUMBER})
        if("${DAY_NUMBER}" MATCHES "^[1-9]$")
            set(DAY_FILENAME "0${DAY_NUMBER}")
        endif()

        set(FILENAME "${CMAKE_SOURCE_DIR}/inputs/${YEAR_NUMBER}/year${YEAR_NUMBER}_day${DAY_FILENAME}.txt")
        if(NOT EXISTS ${FILENAME})
            set(FILENAME "")
        endif()
        string(APPEND INPUTS_CONTENT "\"${FILENAME}\",\n")
    endforeach()

    string(APPEND INPUTS_CONTENT "},\n")
endforeach()

configure_file(
    ${CMAKE_SOURCE_DIR}/templates/inputs.h.in
    ${CMAKE_SOURCE_DIR}/src/inputs.h
    @ONLY
)

# Appends day solvers to the factory.
file(GLOB_RECURSE DAY_SOLVERS CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/src/problems/*/year*_day*.h")
list(LENGTH DAY_SOLVERS NB_DAYS)
set(CASES "")
set(INCLUDES "")
set(AVAILABLE_DAYS "")

foreach(DAY_SOLVER ${DAY_SOLVERS})
    get_filename_component(FILENAME ${DAY_SOLVER} NAME_WE)

    string(REGEX MATCH "^year([0-9]+)_day([0-9]+)$" _ ${FILENAME})
    set(YEAR ${CMAKE_MATCH_1})
    set(DAY ${CMAKE_MATCH_2})

    string(APPEND INCLUDES "#include \"problems/${YEAR}/${FILENAME}.h\"\n")
    string(APPEND CASES "            case ${YEAR}${DAY}: return std::make_unique<Year${YEAR}Day${DAY}>();\n")
    string(APPEND AVAILABLE_DAYS "${YEAR}${DAY}, ")
endforeach()

configure_file(
    ${CMAKE_SOURCE_DIR}/templates/solver_factory.h.in
    ${CMAKE_SOURCE_DIR}/src/cli/solver_factory.h
    @ONLY
)

# Creates a library containing all the problems.
file(GLOB_RECURSE PROBLEM_FILES CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/src/problems/*/*.cpp")
set(PROBLEMS_LIB problems)
add_library(${PROBLEMS_LIB} STATIC ${PROBLEM_FILES})
target_include_directories(${PROBLEMS_LIB} PRIVATE "${CMAKE_SOURCE_DIR}/src")
set_target_properties(${PROBLEMS_LIB} PROPERTIES LINKER_LANGUAGE CXX)

# Creates a library containing all the utilities.
file(GLOB UTILITY_FILES CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/src/aoc_utils/*.cpp")
set(UTILS_LIB utilities)
add_library(${UTILS_LIB} STATIC ${UTILITY_FILES})
set_target_properties(${UTILS_LIB} PROPERTIES LINKER_LANGUAGE CXX)

# Generates the final executable.
add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE ${PROBLEMS_LIB} ${UTILS_LIB})
target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_SOURCE_DIR}/src")
