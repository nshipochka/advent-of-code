#include "../solutions/utilities.h"

#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <fstream>

struct Equation {
    long long test_value;
    std::vector<long long> equation_values;

    Equation(long long test_value, const std::vector<long long>& equation_values)
        : test_value(test_value), equation_values(equation_values) {}
};

std::vector<Equation> read_equations(std::ifstream& in) {
    std::vector<Equation> equations;
    std::string line;
    while (getline(in, line)) {
        std::stringstream ss(line);

        // Parse the test_value
        long long test_value;
        ss >> test_value;
        ss.get(); // Skip ':'

        // Parse the list of numbers
        std::vector<long long> equation_values;
        long long num;
        while (ss >> num) {
            equation_values.push_back(num);
        }

        equations.emplace_back(test_value, equation_values);
    }

    return equations;
}

long long concat(long long lhs, long long rhs) {
    long long multiplier = 1;
    while (multiplier <= rhs) {
        multiplier *= 10;
    }
    return lhs * multiplier + rhs;
}

// Part 1
bool evaluate(const std::vector<long long>& values, int pos, long long current, long long target) {
    if (pos == values.size()) {
        return current == target;
    }

    return evaluate(values, pos + 1, current + values[pos], target) ||
        evaluate(values, pos + 1, current * values[pos], target);
}

// Part 2
bool evaluate_total(const std::vector<long long>& values, int pos, long long current, long long target) {
    if (pos == values.size()) {
        return current == target;
    }

    return evaluate_total(values, pos + 1, current + values[pos], target) ||
        evaluate_total(values, pos + 1, current * values[pos], target) ||
        evaluate_total(values, pos + 1, concat(current, values[pos]), target);
}

long long sum_valid_test_values(const std::vector<Equation>& equations) {
    long long sum = 0;
    for (const auto& eq : equations) 
        if (evaluate_total(eq.equation_values, 1, eq.equation_values[0], eq.test_value))
            sum += eq.test_value;

    return sum;
}

int main() {
    try {
        std::ifstream in = open_file("07");
        if (!in) return 1;
      
        std::vector<Equation> equations = read_equations(in);
        std::cout << sum_valid_test_values(equations) << std::endl;
    }
    catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
        return 1;
    }

    return 0;
}
