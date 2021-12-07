#include<iostream>

//Part 1
int processInput() {
	int last, curr, ctr = 0;
	std::cin >> last;

	while (std::cin >> curr) {
		if (curr > last)
			ctr++;

		last = curr;
	}

	return ctr;
}

int main() {
	std::cout << processInput();
	return 0;
}