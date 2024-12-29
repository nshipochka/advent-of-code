// day-14.cpp
// Solution for day 14
#include "utilities.h"
#include <regex>
#include <algorithm>

using std::pair;

template <const int WIDTH, const int HEIGHT>
pair<Point<int>, Direction>  parse_robot(string s) {
	// (-?\d+): Matches an optional negative sign (-?) followed by one or more digits (\d+).
	// \s* : Matches zero or more whitespace characters.
	std::regex pattern(R"(p=(-?\d+),(-?\d+)\s*v=(-?\d+),(-?\d+))");
	std::smatch match;

	if (std::regex_match(s, match, pattern)) {
		return pair<Point<int>, Direction>(Point(stoi(match[1].str()), stoi(match[2].str())),
			Direction(stoi(match[3].str()), stoi(match[4].str())));
	}
}

template <const int WIDTH, const int HEIGHT>
vector<pair<Point<int>, Direction>>  parse_robots(std::ifstream& in) {
	vector<pair<Point<int>, Direction>> robots;
	string s;
	while (getline(in, s)) {
		robots.push_back(parse_robot<WIDTH, HEIGHT>(s));
	}
	return robots;
}

template <const int WIDTH, const int HEIGHT>
void move_robot(pair<Point<int>, Direction>& robot, int seconds) {
	Point<int> start = robot.first;
	Direction velocity = robot.second;
	int new_x = (start.x + velocity.dx * seconds) % WIDTH;
	int new_y = (start.y + velocity.dy * seconds) % HEIGHT;

	new_x = new_x < 0 ? new_x + WIDTH : new_x;
	new_y = new_y < 0 ? new_y + HEIGHT : new_y;

	robot.first = Point(new_x, new_y);
}

template <const int WIDTH, const int HEIGHT>
void move_robots(vector<pair<Point<int>, Direction>>& robots, int seconds) {
	for (auto& robot : robots)
		move_robot<WIDTH, HEIGHT>(robot, seconds);
}

template <const int MIN_W, const int MAX_W, const int MIN_H, const int MAX_H>
bool is_in_quadrant(Point<int> p) {
	bool horizontal = p.x >= MIN_W && p.x < MAX_W;
	bool vertical = p.y >= MIN_H && p.y < MAX_H;

	return horizontal && vertical;
}

template <const int MIN_W, const int MAX_W, const int MIN_H, const int MAX_H>
int count_in_quadrant(const vector<pair<Point<int>, Direction>>& robots) {
	int count = 0;
	for (const auto& robot : robots) {
		if (is_in_quadrant<MIN_W, MAX_W, MIN_H, MAX_H>(robot.first))
			count++;
	}

	return count;
}

template <const int WIDTH, const int HEIGHT>
int quadrant_product(const vector<pair<Point<int>, Direction>>& robots) {
	int q1 = count_in_quadrant<0, (WIDTH / 2), 0, (HEIGHT / 2)>(robots);
	int q2 = count_in_quadrant<(WIDTH / 2 + 1), WIDTH, 0, (HEIGHT / 2)>(robots);
	int q3 = count_in_quadrant<0, (WIDTH / 2), (HEIGHT / 2 + 1), HEIGHT>(robots);
	int q4 = count_in_quadrant<(WIDTH / 2 + 1), WIDTH, (HEIGHT / 2 + 1), HEIGHT>(robots);
	
	return q1 * q2 * q3 * q4;
}

int main() {
	std::ifstream in = open_file("14");
	if (!in) return 1;

	const int WIDTH = 101;
	const int HEIGHT = 103;

	vector<pair<Point<int>, Direction>> robots = parse_robots<WIDTH, HEIGHT>(in);
	move_robots<WIDTH, HEIGHT>(robots, 100);

	std::cout << quadrant_product<WIDTH, HEIGHT>(robots);

	in.close();
	return 0;
}