#!/bin/bash

# Runs a C++ executable to compute the answer for an Advent of Code puzzle.
# Expects three command line arguments:
# (1) The event year of the puzzle. Must be a number between 2015 and 2023, with no padding.
# (2) The day number of the puzzle. Must be a number between 1 and 25, with no padding.
# (3) The part number of the puzzle. Must be either 1 or 2.


# If the number of command line arguments is wrong, exits.
if [[ $# -ne 3 ]]; then
	echo "ERROR: incorrect number of arguments"
	echo "USAGE: ./run.sh <year> <day> <part>"
	exit
fi

# If the year is invalid, exits.
re="^20(1[5-9]|2[0-3])$"
if [[ ! $1 =~ $re ]]; then
	echo "ERROR: <year> must be an integer between 2015 and 2023, inclusive"
	exit
fi

# If the day is invalid, exits.
re="^([1-9]|1[0-9]|2[0-5])$"
if [[ ! $2 =~ $re ]]; then
	echo "ERROR: <day> must be an integer between 1 and 25, inclusive"
	exit
fi

# Specifies the path of C++ files and test file of the day.
padded_day=$(printf "%02d" $2)

day_files="src/$1/day${padded_day}.cpp"
test_file="inputs/$1/day${padded_day}.txt"

# Compiles and runs the program.
g++ -g $day_files main.cpp "includes/aoc.a" -o main.exe -Wall -Wextra -std=c++17 && ./main.exe $test_file $3
