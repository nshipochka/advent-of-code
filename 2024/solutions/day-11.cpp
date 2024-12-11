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

std::pair<long long, long long> split_stone(long long stone, size_t half) {
	string st = std::to_string(stone);

	string left_half = st.substr(0, half);
	string right_half = st.substr(half);

	return { stoll(left_half), stoll(right_half) };
}

void blink(unordered_map<long long, long long>& stones) {
	unordered_map<long long, long long> updated_stones;

	for (auto& [stone, count] : stones) {
		int digits = (int)log10(stone) + 1;

		if (stone == 0) {
			updated_stones[1] += count;
		}
		else if (digits % 2 == 0) {
			auto split = split_stone(stone, digits / 2);
			updated_stones[split.first] += count;
			updated_stones[split.second] += count;

		}
		else {
			long long multiplied = stone * 2024;
			updated_stones[multiplied] += count;
		}
	}
	std::swap(updated_stones, stones);
}

// Blink n times
void blink(unordered_map<long long, long long>& stones, int n) {
	for (int i = 0; i < n; ++i) {
		blink(stones);
		/*for (auto [stone, cnt] : stones)
			for (int i = 0; i < cnt; ++i)
				std::cout << stone << " ";

		std::cout << std::endl;*/
	}
}

long long count_stones(const unordered_map<long long, long long>& stones) {
	long long count = 0;
	for (auto [stone, cnt] : stones)
		count += cnt;

	return count;
}

int main() {
	std::ifstream in = open_file("11");
	if (!in) return 1;

	string input;	
	getline(in, input);

	unordered_map<long long, long long> stones;
	std::stringstream stream(input);
	string stone;

	while (stream >> stone)
		stones[stoll(stone)]++;

	for (const auto& [stone, count] : stones)
		std::cout << stone << " ";
	std::cout << std::endl;

	blink(stones, 75);
	std::cout << count_stones(stones) << std::endl;

	in.close();
	return 0;
}
