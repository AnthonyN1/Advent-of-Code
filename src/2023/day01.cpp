/*
	Advent of Code - 2023: Day 01
	Author: Anthony Nool (AnthonyN1)
*/

#include <algorithm>
#include <iostream>
#include <iterator>
#include <regex>
#include <string>
#include <unordered_map>
#include <vector>


/**
 * @brief Parses the puzzle input for part two.
 * 
 * @param input  the puzzle input
 * 
 * @return the input, parsed into a convenient data structure.
*/
std::vector<std::string> parseInputPartOne(const std::vector<std::string> &input){
	std::vector<std::string> parsedInput;

	// Extracts only the digits in the strings.
	std::transform(input.cbegin(), input.cend(), std::back_inserter(parsedInput), [](const auto &str){
		std::string digits = "";
		std::copy_if(str.begin(), str.end(), std::back_inserter(digits), [](auto ch){ return isdigit(ch); });
		
		return digits;
	});

	return parsedInput;
}

/**
 * @brief Parses the puzzle input for part two.
 * 
 * @param input  the puzzle input
 * 
 * @return the input, parsed into a convenient data structure.
*/
std::vector<std::string> parseInputPartTwo(const std::vector<std::string> &input){
	std::vector<std::string> parsedInput;

	const std::unordered_map<std::string, std::string> mappings = {
		{"one", "one1one"}, {"two", "two2two"}, {"three", "three3three"}, {"four", "four4four"},
		{"five", "five5five"}, {"six", "six6six"}, {"seven", "seven7seven"},
		{"eight", "eight8eight"}, {"nine", "nine9nine"}
	};

	std::transform(input.cbegin(), input.cend(), std::back_inserter(parsedInput), [&mappings](const auto &str){
		// Converts the spelled out digits into numerical digits.
		std::string spelledOut = str;
		std::for_each(mappings.cbegin(), mappings.cend(), [&spelledOut](const auto &pair){
			spelledOut = std::regex_replace(spelledOut, std::regex(pair.first), pair.second);
		});

		// Extracts only the digits in the strings.
		std::string digits = "";
		std::copy_if(spelledOut.begin(), spelledOut.end(), std::back_inserter(digits), [](auto ch){ return isdigit(ch); });

		return digits;
	});

	return parsedInput;
}


/**
 * @param nums  a collection of strings
 * 
 * @return the sum of the strings using only the first and last digits of each string.
*/
unsigned long long sumFirstAndLast(const std::vector<std::string> &nums){
	unsigned long long sum = 0;
	std::for_each(nums.cbegin(), nums.cend(), [&sum](const auto &digits){
		sum += (digits[0] - '0') * 10 + (digits[digits.size() - 1] - '0');
	});

	return sum;
}


void partOne(const std::vector<std::string> &input){
	std::vector<std::string> parsedInput = parseInputPartOne(input);

	unsigned long long sum = sumFirstAndLast(parsedInput);

	std::cout << sum << std::endl;
}

void partTwo(const std::vector<std::string> &input){
	std::vector<std::string> parsedInput = parseInputPartTwo(input);

	unsigned long long sum = sumFirstAndLast(parsedInput);

	std::cout << sum << std::endl;
}
