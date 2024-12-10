#ifndef __UTILITIES__
#define __UTILITIES__

#include<fstream>
#include<iostream>
#include<string>
#include<vector>
#include<sstream>
#include<algorithm>

using std::vector;
using std::string;
using std::pair;

/*
	<day> has one of the following formats:
	- 0x if x is < 10
	- x if x is >= 10
	- 0x-test or x-test if we want to use the sample input
*/
std::ifstream open_file(const std::string& day) {
	std::string filename("../input-files/day-" + day + "-input.txt");
	std::ifstream in(filename);
	if (!in)
		std::cerr << "Error: Unable to open file.\n";

	return in;
}

/*
	Parses a csv string into a vector<int>
*/
std::vector<int> to_vector(const std::string& input) {
	std::stringstream ss(input);

	std::vector<int> v;
	std::string token;
	size_t index = 0;

	while (getline(ss, token, ',')) {
		v.push_back(stoi(token));
	}

	return v;
}

/*
	Splits the string into characters
*/
std::vector<char> split_to_chars(const std::string& str) {
	std::vector<char> tokens;
	std::stringstream ss(str);
	
	char token;
	while (ss.get(token))
		tokens.push_back(token);

	return tokens;
}

/*
	Splits the string into tokens
*/
std::vector<std::string> split_to_tokens(const std::string& str, char delim) {
	std::vector<std::string> tokens;
	std::stringstream ss(str);

	std::string token;
	while (getline(ss, token, delim))
		tokens.push_back(token);

	return tokens;
}

template <typename T>
using matrix = std::vector<std::vector<T>>;

template <typename T, typename Function>
void input_matrix(std::ifstream& in, matrix<T>& m, const Function& split) {
	std::string line;
	while (getline(in, line)) {
		m.push_back(split(line));
	}
}

template <typename T>
void print_matrix(matrix<T>& m) {
	for (auto row : m) {
		for (auto element : row)
			std::cout << element;
		std::cout << std::endl;
	}
}

#endif