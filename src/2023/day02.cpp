/*
	Advent of Code - 2023: Day 02
	Author: Anthony Nool (AnthonyN1)
*/

#include <algorithm>
#include <iostream>
#include <iterator>
#include <map>
#include <numeric>
#include <regex>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

typedef std::map<std::string, unsigned long long> game_info;


/**
 * @brief Parses the puzzle input for part two.
 * 
 * @param input  the puzzle input
 * 
 * @return the input, parsed into a convenient data structure.
*/
std::unordered_map<unsigned long long, game_info> parseInputPartOne(const std::vector<std::string> &input){
	std::unordered_map<unsigned long long, game_info> parsedInput;

	std::transform(input.cbegin(), input.cend(), std::inserter(parsedInput, parsedInput.end()), [](const auto &str){
		// Gets the game ID.
		const auto spaceIdx = str.find_first_of(' ');
		const auto colonIdx = str.find_first_of(':');
		const unsigned long long gameId = std::stoi(str.substr(spaceIdx + 1, colonIdx - spaceIdx));

		// Creates a dictionary mapping a cube's color to its number of occurrences.
		// For each game, only the highest number of occurrences is recorded.
		game_info gi;

		std::string search = str;
		std::smatch results;
		const std::regex re("(\\d+) (\\w+)");

		while(std::regex_search(search, results, re)){
			const unsigned long long numCubes = std::stoi(results[1]);
			const std::string color = results[2];

			const auto hasColor = gi.find(color) != gi.end();
			if(hasColor && gi.at(color) < numCubes){
				gi[color] = numCubes;
			} else if(!hasColor){
				gi.insert(std::make_pair(color, numCubes));
			}

			search = results.suffix().str();
		}
		
		return std::make_pair(gameId, gi);
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
std::unordered_map<unsigned long long, game_info> parseInputPartTwo(const std::vector<std::string> &input){
	return parseInputPartOne(input);
}


/**
 * @param game     the information of the shown cubes in a game
 * @param maximum  the maximum number of cubes possible
 * 
 * @return true if and only if the game is possible given the maximum number of cubes, else otherwise.
*/
bool isPossible(const game_info &game, const game_info &maximum){
	auto gameItr = game.cbegin();
	auto maximumItr = maximum.cbegin();

	while(maximumItr != maximum.cend()){
		if(gameItr == game.cend()) return false;
		
		if(gameItr->first < maximumItr->first) return false;
		if(gameItr->first > maximumItr->first){ ++maximumItr; continue; }

		if(gameItr->second > maximumItr->second) return false;
		else{ ++gameItr; ++maximumItr; continue; }
	}

	return true;
}


void partOne(const std::vector<std::string> &input){
	std::unordered_map<unsigned long long, game_info> parsedInput = parseInputPartOne(input);

	// This configuration is the maximum number of occurrences possible for each color.
	const game_info maximum = {
		{"red", 12}, {"green", 13}, {"blue", 14}
	};

	unsigned long long sum = std::accumulate(parsedInput.cbegin(), parsedInput.cend(), 0, [&maximum](auto val, const auto &game){
		return val + (isPossible(game.second, maximum) ? game.first : 0);
	});

	std::cout << sum << std::endl;
}

void partTwo(const std::vector<std::string> &input){
	std::unordered_map<unsigned long long, game_info> parsedInput = parseInputPartTwo(input);

	// Calculates the sum of the product of the highest cube occurrences.
	unsigned long long sum = std::accumulate(parsedInput.cbegin(), parsedInput.cend(), 0, [](auto val, const auto &game){
		unsigned long long power = std::accumulate(game.second.begin(), game.second.end(), 1, [](auto innerVal, const auto &cube){
			return innerVal * cube.second;
		});

		return val + power;
	});

	std::cout << sum << std::endl;
}
