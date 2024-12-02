#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<string>

using std::vector;
using std::string;
using std::stringstream;

void input_vectors(std::ifstream& in, vector<vector<int>>& v) {
	string line;
	while (getline(in, line)) {
		stringstream ss(line);
		vector<int> line_v;
		int n;
		while(ss >> n)
			line_v.push_back(n);
		v.push_back(line_v);
	}
}

// Part 1
bool is_safe(const vector<int>& report) {
	if (report.size() <= 1)
		return true;

	bool is_increasing = report[0] < report[1] ? true : false;
	for (vector<int>::const_iterator i = report.begin(); i + 1 != report.end(); ++i) {
		if (is_increasing && *i > *(i + 1))
			return false;

		if (!is_increasing && *i < *(i + 1))
			return false;

		if (*i == *(i + 1))
			return false;

		if (abs(*i - *(i + 1)) > 3)
			return false;
	}

	return true;
}

// Part 2
bool is_safe_w_dampening(vector<int> report) {
	bool is_safe_total = false;

	for (vector<int>::iterator i = report.begin(); i != report.end(); ++i) {
		int curr_element = *i;
		i = report.erase(i);
		is_safe_total = is_safe_total || is_safe(report);
		i = report.insert(i, curr_element);
	}

	return is_safe_total;
}


int get_safe_count(const vector<vector<int>>& reports) {
	int count = 0;
	for (vector<vector<int>>::const_iterator i = reports.begin(); i != reports.end(); ++i)
		if (is_safe(*i) || is_safe_w_dampening(*i))
			count++;

	return count;
}


int main() {
	std::ifstream in("day2-input.txt");
	if (!in) {
		std::cerr << "Error: Unable to open file.\n";
		return 1;
	}

	vector<vector<int>> reports;
	input_vectors(in, reports);

	std::cout << get_safe_count(reports) << std::endl;

	in.close();

	return 0;
}