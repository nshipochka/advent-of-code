#ifndef __UTILITIES__
#define __UTILITIES__

#include<fstream>
#include<iostream>
#include<string>

/*
	<day> has one of the following formats:
	- 0x if x is < 10
	- x if x is >= 10
	- 0x-test or x-test if we want to use the sample input
*/
std::ifstream open_file(const std::string& day) {
	std::string filename("../input_files/day-" + day + "-input.txt");
	std::ifstream in(filename);
	if (!in)
		std::cerr << "Error: Unable to open file.\n";

	return in;
}

#endif