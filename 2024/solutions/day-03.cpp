#include "utilities.h"

#include <regex>
#include <sstream>

int sum_correct_commands(const std::string& input) {
    std::regex pattern(R"(mul\((\d+),(\d+)\))");
    std::smatch match;

    // Iterate through all matches in the string
    std::sregex_iterator i(input.begin(), input.end(), pattern);
    std::sregex_iterator end;

    int sum = 0;

    for (; i != end; ++i) {
        std::smatch match = *i;

        std::string num1_str = match[1].str();
        std::string num2_str = match[2].str();

        int num1 = std::stoi(num1_str);
        int num2 = std::stoi(num2_str);

        std::cout << "mul(" << num1 << "," << num2 << ")\n";
        sum += (num1 * num2);
    }

    return sum;
}

int sum_if_enabled(const std::string& input) {
    std::regex pattern(R"((do\(\))|(don't\(\))|(mul\((\d+),(\d+)\)))");
    
    bool mul_enabled = true;

    std::sregex_iterator i(input.begin(), input.end(), pattern);
    std::sregex_iterator end;

    int sum = 0;

    for (; i != end; ++i) {
        std::smatch match = *i;

        if (match[1].matched) {
            mul_enabled = true;
        }
        else if (match[2].matched) {
            mul_enabled = false;
        }
        else if (match[3].matched) {
            if (mul_enabled) {
                int num1 = std::stoi(match[4].str()); // First number
                int num2 = std::stoi(match[5].str()); // Second number

                sum += num1 * num2;
            }
        }
    }

    return sum;
}

int main() {
	std::ifstream in = open_file("03");
	if (!in) return 1;

    std::ostringstream buffer;
    buffer << in.rdbuf();

    std::string input(buffer.str());

    std::cout << sum_if_enabled(input) << std::endl;

	in.close();
	return 0;
}