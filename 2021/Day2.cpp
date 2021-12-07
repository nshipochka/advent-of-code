#include<iostream>

const unsigned MAX_LEN = 1024;

//void changePosition(int& x, int& y, int n, char* str) {
//	if (!strcmp(str, "up"))
//		y -= n;
//	else if (!strcmp(str, "down"))
//		y += n;
//	else if (!strcmp(str, "forward"))
//		x += n;
//}

void changePosition(int& x, int& y, int& aim, int n, char* str) {
		if (!strcmp(str, "up"))
			aim -= n;
		else if (!strcmp(str, "down"))
			aim += n;
		else if (!strcmp(str, "forward")) {
			x += n;
			y += aim * n;
		}
}

void processInput(int& x, int& y, int& aim) {
	char str[MAX_LEN];
	int n;

	while (std::cin >> str) {
		std::cin >> n;

		changePosition(x, y, aim, n, str);
	}

	std::cout << x << ' ' << y << " " << aim << '\n';
}

int main() {
	int x = 0, y = 0, aim = 0;

	processInput(x, y, aim);

	std::cout << x << ' ' << y << " " << aim << '\n';
	std::cout <<"fajhfskj\n";
	std::cout << x * y;
	return 0;
}