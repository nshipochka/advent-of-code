#include "utilities.h"

vector<int> parse_diskmap(const string& diskmap) {
	vector<int> blocks;
	int file_id = 0;

	for (size_t i = 0; i < diskmap.size(); i++) {
		int length = diskmap[i] - '0';
		int to_insert = -1;

		if (i % 2 == 0)
			to_insert = file_id++;

		// We insert file_id length times
		blocks.insert(blocks.end(), length, to_insert);
	}

	return blocks;
}

// Part 1
void defragment(vector<int>& fs) {
	for (size_t read = fs.size() - 1, write = 0; write <= read;) {
		if (fs[write] != -1) write++;
		else if (fs[read] == -1) read--;
		else std::swap(fs[read], fs[write]);
	}
}

long long checksum(vector<int>& fs) {
	long long sum = 0;
	for (size_t i = 0; i < fs.size() && fs[i] != -1; ++i)
		sum += (long long)(i)*fs[i];

	return sum;
}

// Part 2
vector<vector<int>> compact_filespans(vector<int>& fs) {
	vector<vector<int>> compacted_fs;

	for (size_t i = 0; i < fs.size();) {
		vector<int> span;
		int id = fs[i];

		while (i < fs.size() && fs[i] == id) {
			span.push_back(fs[i]);
			++i;
		}

		compacted_fs.push_back(span);
	}

	return compacted_fs;
}

// Loops infinetely simewhere
void defragment(vector<vector<int>>& fs) {
	for (size_t read = fs.size() - 1; read != static_cast<size_t>(-1); --read) {
		if (fs[read][0] == -1) continue; // Skip free spaces

		size_t file_size = fs[read].size();
		int file_id = fs[read][0];

		// Search for the first free with enough space
		for (size_t write = 0; write < read; ++write) {
			if (fs[write][0] == -1 && fs[write].size() >= file_size) {
				fs.insert(fs.begin() + write, fs[read]);
				fs[read + 1] = vector<int>(file_size, -1);
				fs[write + 1].erase(fs[write + 1].begin(), fs[write + 1].begin() + file_size);
				if (fs[write + 1].empty()) {
					fs.erase(fs.begin() + write + 1);
				}
 
				break;
			}
		}
	}
}


long long checksum(const vector<vector<int>>& fs) {
	long long sum = 0;

	for (size_t i = 0, position = 0; i < fs.size(); ++i) {
		const vector<int>& file_blocks = fs[i];

		for (size_t j = 0; j < file_blocks.size(); ++j) {
			if (file_blocks[j] != -1) { 
				int file_id = file_blocks[j];
				sum += position * file_id;
			}
		    position++;
		}
	}

	return sum;
}

int main() {
	std::ifstream in = open_file("09");
	if (!in) return 1;

	string input;
	getline(in, input);

	vector<int> filesystem = parse_diskmap(input);
	/*for (int block : filesystem) std::cout << block << " ";
	std::cout << std::endl;*/

	vector<vector<int>> compacted_fs = compact_filespans(filesystem);
	/*for (auto block : compacted_fs) {
		for (auto elem : block)
			std::cout << elem << " ";
		std::cout << std::endl;
	}*/


	//defragment(filesystem);
	defragment(compacted_fs);
	/*for (auto block : compacted_fs) {
		for (auto elem : block)
			std::cout << elem << " ";
		std::cout << std::endl;
	}*/

	std::cout << checksum(compacted_fs);

	in.close();
	return 0;
}