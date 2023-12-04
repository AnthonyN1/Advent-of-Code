#!/bin/bash

# Creates subdirectories and a starter file for an Advent of Code puzzle.
# Expects two command line arguments:
# (1) The event year of the puzzle. Must be a number between 2015 and 2023, with no padding.
# (2) The day number of the puzzle. Must be a number between 1 and 25, with no padding.
#
# Expects a .env file in the current directory.
# See .example_env.


# If the number of command line arguments is wrong, exits.
if [[ $# -ne 2 ]]; then
	echo "ERROR: incorrect number of arguments"
	echo "USAGE: ./start-day.sh <year> <day>"
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

# Creates the subdirectories.
padded_day=$(printf "%02d" $2)
path_to_dir="src/$1"

mkdir -p $path_to_dir

# Creates a start file from the template.
path_to_file="${path_to_dir}/day${padded_day}.cpp"
cp "template.cpp" $path_to_file
sed -i -e "s/<year>/$1/g" $path_to_file
sed -i -e "s/<day>/${padded_day}/g" $path_to_file

# Gets the Advent of Code session cookie.
source .env

# Gets the input file of the day, and stores it in the output file.
out_file="inputs/$1/day${padded_day}.txt"
curl -A "https://github.com/AnthonyN1/Advent-of-Code by anthonyjnool@gmail.com" "https://adventofcode.com/$1/day/$2/input" -b "session=${session}" --create-dirs -o $out_file

# Opens the code file in Visual Studio Code.
code $path_to_file
