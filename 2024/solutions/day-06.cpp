#include "../solutions/utilities.h"
#include <set>
#include <map>

struct Direction {
	int di, dj;
	Direction(int di = 0, int dj = 0)
		: di(di), dj(dj) {}

	// up:		i = -1 	j = 0
	// right:	i = 0 	j = 1
	// down:	i = -1  j = 0
	// left:	i = 0   j = -1

	void turn_right() {
		if (di == -1 && dj == 0) { // up to right
			di = 0; dj = 1;
		}
		else if (di == 0 && dj == 1) { // right to down
			di = 1; dj = 0;
		}
		else if (di == 1 && dj == 0) { // down to left
			di = 0; dj = -1;
		}
		else if (di == 0 && dj == -1) { // left to up
			di = -1; dj = 0;
		}
	}

};

struct Position {
	int i, j;
	Direction dir;
	Position(int i = 0, int j = 0, Direction dir = Direction())
		: i(i), j(j), dir(dir) {}

	Position move() const {
		return Position(i + dir.di, j + dir.dj, dir);
	}

	bool operator<(const Position& other) const {
		if (i != other.i) return i < other.i;
		if (j != other.j) return j < other.j;

		return false;
	}

	friend bool operator==(const Position& lhs, const Position& rhs);
};

bool operator==(const Position& lhs, const Position& rhs) {
	return lhs.i == rhs.i && lhs.j == rhs.j;
}

bool out_of_bounds(const matrix<char>& m, const Position& pos) {
	return !(pos.i < m.size() && pos.i >= 0 && pos.j < m[0].size() && pos.j >= 0);
}

// Part 1
int follow_path(matrix<char> m, Position pos) {
	if (out_of_bounds(m, pos))
		return 0;

	int steps = 0;
	Position next = pos.move();

	while (!out_of_bounds(m, next)) {
		while (m[next.i][next.j] == '#') {
			pos.dir.turn_right();
			next = pos.move();
		}

		pos = next;
		next = pos.move();
		if (m[pos.i][pos.j] != 'X') {
			steps++;
			m[pos.i][pos.j] = 'X';
		}
	}

	return steps;
}

Position find_start(const matrix<char>& m) {
	for (int i = 0; i < m.size(); ++i)
		for (int j = 0; j < m[i].size(); ++j)
			switch (m[i][j]) {
			case '^':
				return Position(i, j, Direction(-1, 0));
			case '>':
				return Position(i, j, Direction(0, 1));
			case 'v':
				return Position(i, j, Direction(1, 0));
			case '<':
				return Position(i, j, Direction(0, -1));
			}

	return Position(0, 0);
}

// Part 2
bool creates_cycle(matrix<char>& m, const Position& obstacle, const Position& guard) {
	m[obstacle.i][obstacle.j] = '#';

	Position pos = guard;
	Position next = guard.move();

	std::set<Position> visited;
	visited.insert(pos);

	while (!out_of_bounds(m, next)) {
		while (m[next.i][next.j] == '#') {
			pos.dir.turn_right();
			next = pos.move();
		}

		pos = next;
		next = pos.move();

		if (visited.count(pos)) {
			m[obstacle.i][obstacle.j] = '.';
			return true;
		}

		visited.insert(pos);
	}

	m[obstacle.i][obstacle.j] = '.';
	return false;
}

int count_new_obstacles(matrix<char>& m, Position pos){
	if (out_of_bounds(m, pos))
		return 0;

	std::map<Position, bool> cycle_cache;

	int count = 0;
	Position next = pos.move();

	while (!out_of_bounds(m, next)) {
		while (m[next.i][next.j] == '#') {
			pos.dir.turn_right();
			next = pos.move();
		}

		if (m[next.i][next.j] == '.' && !cycle_cache.count(next)) {
			if (creates_cycle(m, next, pos)) {
				cycle_cache[next] = true;
				count++;
			}
			else {
				cycle_cache[next] = false;
			}
		}

		pos = next;
		next = pos.move();
	}

	return count;
}

int main() {
	std::ifstream in = open_file("06");
	if (!in) return 1;

	matrix<char> m;
	input_matrix(in, m, split_to_chars);
	//print_matrix(m);

	Position start = find_start(m);

	//std::cout << start.i << ", " << start.j << std::endl;
	//std::cout << follow_path(m, start) << std::endl;
	std::cout << count_new_obstacles(m, start) << std::endl;

	in.close();
	return 0;
}