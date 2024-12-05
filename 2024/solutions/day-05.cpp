#include "../solutions/utilities.h"
#include <map>
#include <utility>
#include <algorithm>
#include <stdexcept>

/*
	Reads first part of the file, which is rules
*/
void read_rules(std::ifstream& in, std::multimap<int, int>& rules) {
	std::string line;
	while (getline(in, line) && line != "") {
		std::vector<std::string> tokens = split_to_tokens(line, '|');
		rules.emplace(stoi(tokens[0]), stoi(tokens[1]));
	}
}

/*
	Reads second part of the file, which is the updates
*/
void read_updates(std::ifstream& in, std::vector<std::vector<int>>& updates) {
	std::string line;
	while (getline(in, line))
		updates.push_back(to_vector(line));
}

/*
	Checks if an update is correctly structured
*/
bool check_update(const std::vector<int>& update, const std::multimap<int, int>& rules) {
	for(int i = 0; i < update.size(); ++i) {
		auto page_rules = rules.equal_range(update[i]);

		// Iterate through all the rules for this page
		for (auto it = page_rules.first; it != page_rules.second; ++it) {
			auto rule_occurrence = find(update.begin(), update.end(), it->second);
			std::size_t rule_index = std::distance(std::begin(update), rule_occurrence);
			
			// If the current page occured before a restrction
			if(i > rule_index)
				return false;
		}
	}

	return true;
}

/*
	A compare function to compare two pages according to the partial order in rules
*/
bool compare(int a, int b, const std::multimap<int, int>& rules) {
	// Check if there is a rule for a < b
	auto range = rules.equal_range(a);
	for (auto it = range.first; it != range.second; ++it) {
		if (it->second == b) return true;
	}

	// Check if there is a rule that for b < a
	range = rules.equal_range(b);
	for (auto it = range.first; it != range.second; ++it) {
		if (it->second == a) return false;
	}

	// If no rule exists, we leave the order unchanged
	return false;
}

/*
	Returns a sorted update according to the partial order in rules
*/
std::vector<int> order(const std::vector<int>& update, const std::multimap<int, int>& rules) {
	std::vector<int> update_copy = update;
	std::stable_sort(update_copy.begin(), update_copy.end(), 
		[&rules](int a, int b) { 
			return compare(a, b, rules); 
		});

	return update_copy;
}

int get_middle(const std::vector<int>& v) {
	return v[v.size() / 2];
}

int main() {
	std::ifstream in = open_file("05");
	if (!in) return 1;

	std::multimap<int, int> rules;
	std::vector<std::vector<int>> updates;

	try {
		read_rules(in, rules);
		read_updates(in, updates);

	}
	catch (std::exception& e) {
		std::cerr << "Reading input error: " << e.what();
	}
	
	int sum = 0;
	int sum_reordered = 0;
	for (auto u : updates) {
		if (check_update(u, rules))
			sum += get_middle(u);
		else 
			sum_reordered += get_middle(order(u, rules));
	}

	std::cout << sum << std::endl;
	std::cout << sum_reordered << std::endl;

	in.close();
	return 0;
}