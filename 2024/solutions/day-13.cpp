// day-13.cpp
// Solution for day 13
#include "utilities.h"
#include <regex>

struct Machine {
	Point<long long> prize; // X, Y
	Direction A; // Ax, Ay
	Direction B; // Bx, By
	
	Machine(Machine&& other)
		: prize(other.prize), A(std::move(other.A)), B(std::move(other.B))
	{}

	Machine(Point<long long> prize, Direction A, Direction B)
		: prize(prize), A(A), B(B) {
	}
};

Direction parse_button(string s) {
	std::regex pattern(R"(Button\s([A|B]):\sX\+(\d+),\sY\+(\d+))");
	std::smatch match;

	Direction dir;

	if (std::regex_match(s, match, pattern) && match.size() == 4) {
		dir.dx = std::stoi(match[2].str()); // Extract X value
		dir.dy = std::stoi(match[3].str()); // Extract Y value
	}

	return dir;
}

Point<long long> parse_prize(string s) {
	std::regex pattern(R"(Prize:\sX=(\d+),\sY=(\d+))");
	std::smatch match;

	Point<long long> prize;

	if (std::regex_match(s, match, pattern) && match.size() == 3) {
		prize.x = std::stoll(match[1].str()) + 10000000000000; // Extract X value
		prize.y = std::stoll(match[2].str()) + 10000000000000; // Extract Y value
	}

	//std::cout << prize << std::endl;

	return prize;
}

Machine parse_input(std::ifstream& in) {
	string buff;
	// Button A: X+94, Y+34
	getline(in, buff);
	Direction A = parse_button(buff);

	// Button B: X+22, Y+67
	getline(in, buff);
	Direction B = parse_button(buff);

	//Prize: X=8400, Y=5400
	getline(in, buff);
	Point<long long> prize = parse_prize(buff);

	// newline
	getline(in, buff);

	return Machine(prize, A, B);
}

long long solve(const Machine& machine) {
	long long numerator = machine.prize.y * (long long)machine.A.dx - machine.prize.x * (long long)machine.A.dy;
	long long denominator = (long long)machine.B.dy * (long long)machine.A.dx - (long long)machine.A.dy * (long long)machine.B.dx;
	
	if (!denominator || numerator % denominator)
		return -1;

	long long b = numerator / denominator;
	long long a = 0;

	if (machine.A.dx == 0) {
		if ((long long)(machine.prize.y - machine.B.dy * b) % machine.A.dy) {
			a = (machine.prize.y - machine.B.dy * b) / machine.A.dy;
		}
	}
	else {
		a = (machine.prize.x - machine.B.dx * b) / machine.A.dx;
	}

	if (a < 0 || b < 0)
		return -1;

	return 3*a + b;
}

vector<Machine> parse_all(std::ifstream& in) {
	vector<Machine> vec;
	while (in)
		vec.push_back(parse_input(in));

	//vec.pop_back();
	return vec;
}

unsigned long long solve_all(const vector<Machine>& machines) {
	unsigned long long sum = 0;

	for (const auto& m : machines) {
		long long curr_result = solve(m);
		if (curr_result != -1)
			sum += curr_result;
		
	}

	return sum;
}

int main() {
	std::ifstream in = open_file("13-test");
	if (!in) return 1;

	/*Machine m = parse_input(in);
	std::cout << solve(m);*/

	vector<Machine> m_vec = parse_all(in);

	std::cout << solve_all(m_vec);

	in.close();
	return 0;
}