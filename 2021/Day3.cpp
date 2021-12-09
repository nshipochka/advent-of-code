#include<iostream>
#include<vector>
#include<cassert>

const unsigned max = 1024;

void input(std::vector<std::vector<char>>& vec) {
	char curr[max];
	//std::cout << std::cin.getline(curr, '\n');
	while (std::cin.getline(curr, '\n')) {
		std::cin.get();
		std::vector<char> v;
		char* p = curr;
		while (*p) {
			v.push_back(*p);
			//std::cout << vec.at(vec.size() - 1) << '\n';
			p++;
		}
		//v.push_back('\0');
		vec.push_back(v);
	}
}

unsigned mostCommonAt(const std::vector<std::vector<char>>& vec, int len, int pos) {
	int size = vec.size();

	int ones = 0;
	int zeros = 0;

	for (int i = 0; i < size; ++i) {
		assert(vec[i].size() != 0);
		if (vec[i][pos] - '0') ones++;
		else zeros++;
	}

	return ones > zeros ? 1 : 0;
}

unsigned mostCommon(std::vector<std::vector<char>>& vec, int len) {

	unsigned result = 0;

	for (int i = 0; i < len; ++i) {
		result += mostCommonAt(vec, len, i) * pow(2, len - i - 1);
	}

	return result;
}

unsigned leastCommon(unsigned mostCommon, int len) {
	unsigned mask = 0;
	while (len) {
		mask = mask << 1;
		mask = mask | 1;
		len--;
	}

	return mostCommon ^ mask;
}

int main() {
	std::vector<std::vector<char>> vec;

	input(vec);
	assert(vec.size() != 0);
	int len = vec[0].size();

	unsigned res = mostCommon(vec, len);

	std::cout << res << ", " << leastCommon(res, len) << std::endl;

	//deallocate(vec);
	return 0;
}

