#include "utilities.h"
#include <list>
#include <string>
#include <cmath>
#include <unordered_map>
#include <sstream>
#include <iostream>
using std::vector;
using std::string;
using std::unordered_map;

// Dictionary to cache results
unordered_map<string, vector<string>> cache;

void remove_leading_zeros(string& input_str) {
    input_str = std::to_string(stoll(input_str));  // Convert to number and back to string to remove leading zeros
}

std::pair<string, string> split_stone(const string& stone, size_t half) {
    string left_half = stone.substr(0, half);
    string right_half = stone.substr(half);

    remove_leading_zeros(left_half);
    remove_leading_zeros(right_half);

    return { left_half, right_half };
}

string multiply_string_by_int(const string& number, int multiplier) {
   /* string result = "";
    int carry = 0;

    for (auto rit = number.rbegin(); rit != number.rend(); ++rit) {
        int digit = (*rit - '0') * multiplier + carry;
        result.push_back((digit % 10) + '0');
        carry = digit / 10;
    }

    while (carry > 0) {
        result.push_back((carry % 10) + '0');
        carry /= 10;
    }

    std::reverse(result.begin(), result.end());*/

    long long result = stoll(number) * multiplier;
    return std::to_string(result);
}

// Blink once with caching
void blink(std::vector<string>& stones) {
    vector<string> updated_stones;
    for (auto& stone : stones) {
        vector<string> result;
        // Check if the result of this stone is already cached
        if (cache.find(stone) != cache.end()) {
            result = cache[stone];
        
        }
        else {

            size_t digits = stone.size();

            if (stone == "0") {
                result.push_back("1");
            }
            else if (digits % 2 == 0) {
                auto split = split_stone(stone, digits / 2);
                result.push_back(split.first);
                result.push_back(split.second);

            }
            else {
                string multiplied = multiply_string_by_int(stone, 2024);
                result.push_back(multiplied);
            }

            cache[stone] = result;
        }

        updated_stones.insert(updated_stones.end(), result.begin(), result.end());
    }

    stones = std::move(updated_stones);  // Move the updated stones back into the original container
}

// Blink n times
void blink(vector<string>& stones, int n) {
    for (int i = 0; i < n; ++i) {
        blink(stones);
        /*for (const auto& v : stones) {
            std::cout << v << " ";
        }
        std::cout << std::endl;*/
    }
}

int main() {
    std::ifstream in = open_file("11");
    if (!in) return 1;

    string input;
    getline(in, input);

    vector<string> vec;
    std::stringstream stream(input);
    string stone;

    while (stream >> stone) {
        vec.push_back(stone);
    }

    for (const auto& v : vec) {
        std::cout << v << " ";
    }
    std::cout << std::endl;

    blink(vec, 25);
    std::cout << vec.size() << std::endl;

    in.close();
    return 0;
}
