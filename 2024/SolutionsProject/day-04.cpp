#include"../solutions/utilities.h"

struct Direction {
	// The changes applied to x and y to direct the new direction
	int dx, dy;
	Direction (int dx = 0, int dy = 0)
		:dx(dx), dy(dy) {}

	friend Direction operator+ (const Direction& lhs, const Direction& rhs);
};

Direction operator+ (const Direction& lhs, const Direction& rhs) {
	return Direction(lhs.dx + rhs.dx, lhs.dy + rhs.dy);
}


// idk if this isn't a super cumbersome and stupid representation
// These are direction constants for each direction + an array for easy iteration

const Direction NONE(0, 0);

const Direction DOWN(1, 0);
const Direction UP(-1, 0);
const Direction LEFT(0, -1);
const Direction RIGHT(0, 1);

const Direction DOWN_RIGHT(DOWN + RIGHT);
const Direction DOWN_LEFT(DOWN + LEFT);
const Direction UP_RIGHT(UP + RIGHT);
const Direction UP_LEFT(UP + LEFT);

const Direction directions[] = { DOWN, UP, LEFT, RIGHT, DOWN_RIGHT, DOWN_LEFT, UP_RIGHT, UP_LEFT };

struct Position {
	int x, y;
	Position(int x = 0, int y = 0)
		:x(x), y(y) {}

	void move(Direction d) {
		x += (int)d.dx;
		y += (int)d.dy;
	}
};

// Check if position falls within the matrix
bool is_valid(Position p, int rows, int cols) {
	return p.x >= 0 && p.x < rows && p.y >= 0 && p.y < cols;
}

// Search for the word given a starting position and a direction
bool search_from_pos(const matrix<char>& m, const std::string& word, Position p, Direction d) {
	int rows = m.size();
	int cols = m[0].size();
	int len = word.length();

	Position end = Position(p.x + d.dx * (len - 1), p.y + d.dy * (len - 1));
	if (!is_valid(end, rows, cols))
		return false;

	// Check for the word
	for (int i = 0; i < len; ++i) {
		if (!is_valid(p, rows, cols) || m[p.x][p.y] != word[i])
			return false;

		p.move(d);
	}

	return true;
}

int count_word_occurrences(const matrix<char>& m, const std::string& word) {
	int rows = m.size();
	int cols = m[0].size();
	int count = 0;

	for (int i = 0; i < rows; ++i)
		for (int j = 0; j < cols; ++j)
			// Check from this cell in all directions
			for (const auto& d : directions) {
				Position p(i, j);
				if (search_from_pos(m, word, p, d))
					++count;
			}

	return count;
}

int count_word_x_occurrences(const matrix<char>& m, const std::string& word) {
	int rows = m.size();
	int cols = m[0].size();
	int len = word.length();

	int count = 0;

	for (int i = 0; i <= rows; ++i)
		for (int j = 0; j <= cols; ++j) {
			Position top_left(i, j);
			Position top_right(i, j + len - 1);
			Position bottom_left(i + len - 1, j);
			Position bottom_right(i + len - 1, j + len - 1);

			if (!is_valid(top_left, rows, cols) || !is_valid(top_right, rows, cols) ||
				!is_valid(bottom_left, rows, cols) || !is_valid(bottom_right, rows, cols))
				continue;
			
			bool diagonal1 = search_from_pos(m, word, top_left, DOWN_RIGHT) ||
				search_from_pos(m, word, bottom_right, UP_LEFT);
			bool diagonal2 = search_from_pos(m, word, top_right, DOWN_LEFT) ||
				search_from_pos(m, word, bottom_left, UP_RIGHT);

			if (diagonal1 && diagonal2)
				count++;
		}

	return count;
}

int main() {
	std::ifstream in = open_file("04");
	if (!in) return 1;

	matrix<char> m;
	input_matrix(in, m, split_to_chars);

	std::cout << count_word_occurrences(m, "XMAS") << std::endl;
	std::cout << count_word_x_occurrences(m, "MAS") << std::endl;

	in.close();
	return 0;
}