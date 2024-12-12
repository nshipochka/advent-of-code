#ifndef __UTILITIES__
#define __UTILITIES__

#include<fstream>
#include<iostream>
#include<string>
#include<vector>
#include<sstream>
#include<algorithm>
#include <array>
#include <ostream>

using std::vector;
using std::string;
using std::pair;

// Direction Class
class Direction {
public:
	enum class Type {
		NONE,
		RIGHT,
		DOWN,
		LEFT,
		UP,
		DOWN_RIGHT,
		DOWN_LEFT,
		UP_RIGHT,
		UP_LEFT,
		NUM_DIRECTIONS // Tracks the number of directions
	};

	int dx, dy;
	Type type;

	Direction(int dx = 0, int dy = 0, Type type = Type::NONE)
		: dx(dx), dy(dy), type(type) {
	}

	Direction operator+(const Direction& other) const {
		return Direction(dx + other.dx, dy + other.dy, Type::NONE); // Type is ambiguous after addition
	}

	Direction operator*(int scalar) const {
		return Direction(dx * scalar, dy * scalar, Type::NONE); // Type becomes NONE after scaling
	}

	Direction flip() {
		switch (type) {
		case Type::UP: return all_directions()[(size_t)Type::DOWN];
		case Type::DOWN: return all_directions()[(size_t)Type::UP];
		case Type::LEFT: return all_directions()[(size_t)Type::RIGHT];
		case Type::RIGHT: return all_directions()[(size_t)Type::LEFT];
		default:
			return *this;
		}
	}

	bool operator==(const Direction& other) const {
		return dx == other.dx && dy == other.dy;
	}

	friend std::ostream& operator<<(std::ostream& os, const Direction& dir) {
		return os << "Type: " << static_cast<int>(dir.type)
			<< " (" << dir.dx << ", " << dir.dy << ")";
	}

	// Static utility function to get all directions
	static const std::array<Direction, static_cast<size_t>(Type::NUM_DIRECTIONS)>& all_directions() {
		static const std::array<Direction, static_cast<size_t>(Type::NUM_DIRECTIONS)> directions = {
			Direction(0, 0, Type::NONE),       // NONE
			Direction(0, 1, Type::RIGHT),      // RIGHT
			Direction(1, 0, Type::DOWN),       // DOWN
			Direction(0, -1, Type::LEFT),      // LEFT
			Direction(-1, 0, Type::UP),        // UP
			Direction(1, 1, Type::DOWN_RIGHT), // DOWN_RIGHT
			Direction(1, -1, Type::DOWN_LEFT), // DOWN_LEFT
			Direction(-1, 1, Type::UP_RIGHT),  // UP_RIGHT
			Direction(-1, -1, Type::UP_LEFT)   // UP_LEFT
		};
		return directions;
	}
};



// Point structure
struct Point {
	int x, y;

	Point(int x = 0, int y = 0) : x(x), y(y) {}

	bool is_within_range(int width, int height, int min_x = 0, int min_y = 0) const {
		return x < width && y < height && x >= min_x && y >= min_y;
	}

	// Move the point in a specified direction
	void move(const Direction& dir) {
		x = x + dir.dx;
		y = y + dir.dy;
	}

	// Move using DirectionType
	void move(Direction::Type d) {
		const Direction& dir = Direction::all_directions()[static_cast<size_t>(d)];
		move(dir);
	}

	bool operator==(const Point& other) const {
		return x == other.x && y == other.y;
	}

	bool operator!=(const Point& other) const {
		return !(*this == other);
	}

	friend std::ostream& operator<<(std::ostream& os, const Point& point) {
		return os << "(" << point.x << ", " << point.y << ")";
	}
};

// Matrix class
template <typename T>
class Matrix {
public:
	using value_type = T;

private:
	std::vector<std::vector<T>> data;

public:
	Matrix() {}
	// Constructor to initialize matrix with given dimensions and default value
	Matrix(size_t rows, size_t cols, const T& default_value = T())
		: data(rows, std::vector<T>(cols, default_value)) {
	}

	void push_back(const std::vector<T>& v) {
		data.push_back(v);
	}

	// Access operator using Point
	T& operator[](const Point& p) {
		return data[p.x][p.y];
	}

	const T& operator[](const Point& p) const {
		return data[p.x][p.y];
	}

	// Access operator using row and column indices
	std::vector<T>& operator[](size_t row) {
		return data[row];
	}

	const std::vector<T>& operator[](size_t row) const {
		return data[row];
	}

	// Other utility functions like dimensions
	size_t rows() const { return data.size(); }
	size_t cols() const { return data.empty() ? 0 : data[0].size(); }

	bool empty() const {
		return data.empty();
	}

	friend std::ostream& operator<<(std::ostream& os, const Matrix<T>& matrix) {
		for (const auto& row : matrix.data) {
			for (const auto& element : row) {
				os << element << " "; // Print each element in the row
			}
			os << "\n"; // Newline after each row
		}
		return os;
	}
};

//	Splits the string into characters
std::vector<char> split_to_chars(const std::string& str) {
	std::vector<char> tokens;
	std::stringstream ss(str);

	char token;
	while (ss.get(token))
		tokens.push_back(token);

	return tokens;
}

//	Parses a csv string into a vector<int>
std::vector<int> to_vector(const std::string& input) {
	std::stringstream ss(input);

	std::vector<int> v;
	std::string token;
	size_t index = 0;

	while (getline(ss, token, ',')) {
		v.push_back(stoi(token));
	}

	return v;
}

// Splits the string into tokens of type T
template <typename T>
std::vector<T> split_to_tokens(const std::string& str, char delim) {
	std::vector<T> tokens;
	std::stringstream ss(str);

	std::string token;
	while (getline(ss, token, delim))
		tokens.push_back(token);

	return tokens;
}

// Returns a matrix with input from a stream
template <typename T, typename Function>
Matrix<T> input_matrix(std::ifstream& in, const Function& split) {
	Matrix<T> m;
	std::string line;

	while (getline(in, line))
		m.push_back(split(line));

	return m;
}

//	<day> has one of the following formats:
// - 0x if x is < 10
//	- x if x is >= 10
//	- 0x-test or x-test if we want to use the sample input
std::ifstream open_file(const std::string& day) {
	std::string filename("../input-files/day-" + day + "-input.txt");
	std::ifstream in(filename);
	if (!in)
		std::cerr << "Error: Unable to open file.\n";

	return in;
}
#endif