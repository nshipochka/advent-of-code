#include <iostream>
#include <fstream>
#include <regex>

const int MAX_RED = 12;
const int MAX_GREEN = 13;
const int MAX_BLUE = 14;



int main() {
    std::fstream input;
    input.open("input.txt", std::ios::in);

    if (!input.is_open()) {
        std::cerr << "Input error\n";
        return -1;
    }

    int result = 0;
    std::string line;
    while (std::getline(input, line)) {
        result += calibrationValue2(line);
    }

    input.close();

    std::fstream output;
    output.open("output.txt", std::ios::out);

    if (!output.is_open()) {
        std::cerr << "Output error\n";
        return -1;
    }

    output << result << std::endl;

    output.close();

    return 0;
}