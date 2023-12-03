#include<iostream>
#include<fstream>
#include<vector>
#include<string>

const size_t DIGIT_COUNT = 20;
const std::string DIGITS[DIGIT_COUNT] = { "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine",
                             "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };

std::vector<int> patternPositions(const std::string& s, const std::string& pattern) {
    std::vector<int> positions;
    int found = s.find(pattern);

    while (found != std::string::npos) {
        positions.push_back(found);
        found = s.find(pattern, found + 1);
    }

    return positions;
}

int toInt(const std::string& s) {
    for (size_t i = 0; i < DIGIT_COUNT/2; ++i) {
        if (s == DIGITS[i])
            return i;
    }
    for (size_t i = DIGIT_COUNT/2 ; i < DIGIT_COUNT; ++i) {
        if (s == DIGITS[i])
            return i - DIGIT_COUNT / 2;
    }
}

int calibrationValue2(const std::string& s) {
    int firstPos = INT_MAX;
    int lastPos = INT_MIN;

    std::string first;
    std::string last;

    for (int i = 0; i < DIGIT_COUNT; ++i) {
        std::vector<int> positions = patternPositions(s, DIGITS[i]);

        if (positions.empty())
            continue;

        int min = *std::min_element(positions.begin(), positions.end());
        int max = *std::max_element(positions.begin(), positions.end());

        if (firstPos > min && min != -1) {
            firstPos = min;
            first = DIGITS[i];
        }

        if (lastPos < max && max != -1) {
            lastPos = max;
            last = DIGITS[i];
        }
    }//54468

    return toInt(first) * 10 + toInt(last);
}

int calibrationValue1(const std::string& s) {
    int result = 0;
    size_t len = s.length();
    size_t i = 0;

    for (; i < len && !isdigit(s[i]); ++i);
    if (isdigit(s[i]))
        result += (s[i] - '0') * 10;

    i = len - 1;
    for (; i >= 0 && !isdigit(s[i]); --i);
    if (isdigit(s[i]))
        result += s[i] - '0';

    return result;
}

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