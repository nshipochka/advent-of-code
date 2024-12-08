#include "../solutions/utilities.h"
#include <map>
#include <set>

using std::multimap;
using std::set;

class Vec2 {
public:
	Vec2() : x(0), y(0) {}
	Vec2(int x, int y) : x(x), y(y) {}

	friend bool operator<(const Vec2& lhs, const Vec2& rhs);

	friend Vec2 operator-(const Vec2& lhs, const Vec2& rhs);
	friend Vec2 operator+(const Vec2& lhs, const Vec2& rhs);
	
	template <typename T>
	Vec2 operator*(const T& scalar);

	bool is_within_range(size_t width, size_t height) const {
		return x >= 0 && x < width && y >= 0 && y < width;
	}

	int get_x() const { return x; }
	int get_y() const { return y; }
private:
	int x, y;
};

bool operator<(const Vec2& lhs, const Vec2& rhs) {
	if (lhs.x != rhs.x) {
		return lhs.x < rhs.x;
	}
	return lhs.y < rhs.y;
}

Vec2 operator-(const Vec2& lhs, const Vec2& rhs) {
	return Vec2(lhs.x - rhs.x, lhs.y - rhs.y);
}

Vec2 operator+(const Vec2& lhs, const Vec2& rhs) {
	return Vec2(lhs.x + rhs.x, lhs.y + rhs.y);
}

template<typename T>
Vec2 Vec2::operator*(const T& scalar) {
	return Vec2(x * scalar, y * scalar);
}

multimap<char, Vec2> antenna_types_positions(const matrix<char>& m) {
	multimap<char, Vec2> antennas;
	
	size_t height = m.size();
	size_t width = m[0].size();

	for (size_t y = 0; y < height; ++y)
		for (size_t x = 0; x < width; ++x)
			if (m[x][y] != '.')	
				antennas.emplace(m[x][y], Vec2(x, y));

	return antennas;
}

Vec2 calculate_antinode_position(Vec2 a, Vec2 b) {
	Vec2 vector = b - a;
	return a + vector * 2;
}

set<Vec2> get_antinodes(const multimap<char, Vec2>& antennas) {
	set<Vec2> antinodes;

	// Iterate through each unique key in the multimap
	for (auto it = antennas.begin(); it != antennas.end();) {
		auto range = antennas.equal_range(it->first);

		for (auto outer = range.first; outer != range.second; ++outer) {
			for (auto inner = std::next(outer); inner != range.second; ++inner) {
					// Calculate (a, b) and (b, a)
					antinodes.insert(calculate_antinode_position(outer->second, inner->second));
					antinodes.insert(calculate_antinode_position(inner->second, outer->second));
			}
		}

		it = range.second;
	}

	return antinodes;
}

set<Vec2> calculate_antinode_positions(Vec2 a, Vec2 b, size_t width, size_t height) {
	Vec2 vector = b - a;
	set<Vec2> antinodes;

	size_t i = 0;
	Vec2 antinode_pos = a + vector * i;

	while(antinode_pos.is_within_range(width, height)) {
		antinodes.insert(antinode_pos);
		i++;
		antinode_pos = a + vector * i;
	}

	return antinodes;
}

set<Vec2> get_antinodes_2(const multimap<char, Vec2>& antennas, size_t width, size_t height) {
	set<Vec2> antinodes;

	// Iterate through each unique key in the multimap
	for (auto it = antennas.begin(); it != antennas.end();) {
		auto range = antennas.equal_range(it->first);

		for (auto outer = range.first; outer != range.second; ++outer) {
			for (auto inner = std::next(outer); inner != range.second; ++inner) {
				// Calculate (a, b) and (b, a)
				set<Vec2> res = calculate_antinode_positions(outer->second, inner->second, width, height);
				antinodes.insert(res.begin(), res.end());

				res = calculate_antinode_positions(inner->second, outer->second, width, height);
				antinodes.insert(res.begin(), res.end());
			}
		}

		// Move to the next group of antennas with a different key
		it = range.second;
	}

	return antinodes;
}


void filter_within_range(set<Vec2>& antinodes, size_t width, size_t height) {
	for (auto it = antinodes.begin(); it != antinodes.end();)
		if (!it->is_within_range(width, height))
			it = antinodes.erase(it);
		else it++;
}

void place_antinodes(matrix<char>& m, set<Vec2>& antinodes) {
	for (auto it = antinodes.begin(); it != antinodes.end(); ++it)
		m[it->get_x()][it->get_y()] = '#';
}

int main() {
	std::ifstream in = open_file("08");
	if (!in) return 1;

	matrix<char> m;
	input_matrix(in, m, split_to_chars);
	//print_matrix(m);

	set<Vec2> antinodes = get_antinodes_2(antenna_types_positions(m), m.size(), m[0].size());
	filter_within_range(antinodes, m.size(), m[0].size());
	std::cout << antinodes.size() << std::endl;
	//place_antinodes(m, antinodes);
	//print_matrix(m);

	in.close();
	return 0;
}