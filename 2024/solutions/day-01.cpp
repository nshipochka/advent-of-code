#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

using std::vector;

void input_vectors(std::istream& in, vector<int>& left, vector<int>& right) {
	int l, r;
	while (in >> l && in >> r) {
		left.push_back(l);
		right.push_back(r);
	}
}

// Part 1
int get_difference(vector<int>& left, vector<int>& right) {
	int difference = 0;

	for (auto l = left.begin(), r = right.begin(); l != left.end() && r != right.end(); ++l, ++r) {
		difference += abs(*l - *r);
	}

	return difference;
}

int occurance_count(int n, const vector<int>& v) {
	int count = 0;
	for (auto next_occurance = std::find(v.begin(), v.end(), n); 
		next_occurance != v.end();
		count++,
		next_occurance = std::find(next_occurance + 1, v.end(), n));
	
	return count;
}

// Part 2
int get_similarity(vector<int>& left, vector<int>& right) {
	int similarity = 0;

	for (int n : left)
		similarity += n * occurance_count(n, right);

	return similarity;
}

int main() {
	std::ifstream in("../input_files/day-01-input.txt");
	if (!in) {
		std::cerr << "Error: Unable to open file.\n";
		return 1;
	}
	
	vector<int> left, right;
	input_vectors(in, left, right);
	std::sort(left.begin(), left.end());
	std::sort(right.begin(), right.end());

	std::cout << get_difference(left, right) << std::endl;
	std::cout << get_similarity(left, right) << std::endl;

	in.close();
	return 0;
}