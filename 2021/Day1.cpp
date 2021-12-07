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

//Part 2
int processInputWindows() {
	int curr = 0;
	int arr[3];

	int lastSum = 0;
	int currSum = 0;

	int ctr = 0;

	//first three elements
	for (int i = 0; i < 3; ++i) {
		if (std::cin >> curr) {
			arr[i] = curr;
			lastSum += curr;
		}
	}

	char c = 'A';
	//rest of the elements
	while (std::cin >> curr) {

		for (int i = 0; i < 2; ++i)
			arr[i] = arr[i + 1];

		arr[2] = curr;
		currSum = 0;
		std::cout << c++ << ":" << lastSum << "\n";

		for (int i = 0; i < 3; ++i)
			currSum += arr[i];

		if (currSum > lastSum)
			ctr++;

		
		lastSum = currSum;
	}

	return ctr;
}

int main() {
	std::cout << processInputWindows();
	return 0;
}