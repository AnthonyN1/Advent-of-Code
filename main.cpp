/*
	Advent of Code - Main solver
	Author: Anthony Nool (AnthonyN1)
*/

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>


void partOne(const std::vector<std::string> &input);
void partTwo(const std::vector<std::string> &input);


int main(int argc, char* argv[]){
	// If the number of command line arguments is wrong, returns.
	if(argc != 3){
		std::cerr << "ERROR: incorrect number of arguments\n";
		std::cerr << "USAGE: ./main.exe <input file> <part number>" << std::endl;
		return EXIT_FAILURE;
	}

	// Reads the test in from a text file.
	std::ifstream inStr(argv[1]);
	if(!inStr){
		std::cerr << "ERROR: unable to open input file" << std::endl;
		return EXIT_FAILURE;
	}

	std::vector<std::string> input;
	std::string line;
	while(std::getline(inStr, line))
		input.push_back(line);
	
	// Determines which part to execute.
	std::string part(argv[2]);
	if(part != "1" && part != "2"){
		std::cerr << "ERROR: <part number> must be either 1 or 2" << std::endl;
		return EXIT_FAILURE;
	}
	
	// Runs the function for either part one or part two.
	int partNum = std::stoi(part);
	switch(partNum){
		case 1: partOne(input); break;
		case 2: partTwo(input); break;
	}

	return EXIT_SUCCESS;
}
