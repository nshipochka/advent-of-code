#ifndef __UTILITIES__
#define __UTILITIES__

#include<fstream>
#include<iostream>
#include<string>

// <day> has the format either 0x if day x is < 10
//		 or x otherwise	
std::ifstream open_file(const std::string& day) {
	std::string filename("day-" + day + "-input.txt");
	std::ifstream in(filename);
	if (!in) {
		std::cerr << "Error: Unable to open file.\n";
	}
	return in;
}

#endif