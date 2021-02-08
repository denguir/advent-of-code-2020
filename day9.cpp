#include <iostream>
#include <fstream>
#include <algorithm>
#include "day1.hpp"


int extend(int target, int sum, std::vector<int>& numbers, std::ifstream& infile) {
    int n;
    std::string line;
    while (sum < target && std::getline(infile, line)) {
        if (line.compare("")) {
            n = std::stoi(line);
            numbers.push_back(n);
            sum += n;
        }
    }
    return sum;
}

int shrink(int target, int sum, std::vector<int>& numbers, std::ifstream& infile) {
    int n;
    std::string line;
    while (sum > target && numbers.size() > 2) {
        sum -= numbers[0];
        numbers.erase(numbers.begin());
    }
    return sum;
}

int find_seq(int target, std::vector<int>& numbers, std::ifstream& infile) {
    int sum = 0;
    int minmax = -1;
    while (sum != target && !infile.eof()) {
        if (sum < target) {
            sum = extend(target, sum, numbers, infile);
        } else {
            sum = shrink(target, sum, numbers, infile);
        }
    }
    if (sum == target) {
        auto result = std::minmax_element(numbers.begin(), numbers.end());
        minmax = *result.first + *result.second;
    }
    return minmax;
}

int find_invalid(std::ifstream& infile, int preamble) {
    std::vector<int> numbers;
    int k = 0;
    int n;
    int a, b, prod;
    while (infile >> n) {
        if (k >= preamble) {
            std::tie(a, b, prod) = pair_search(n, numbers);
            numbers.erase(numbers.begin());
            if (prod == -1) {
                return n;
            }
        }
        numbers.push_back(n);
        k++;
    }
    return -1;
}


int main() {
    // comment main fct of day1.cpp to compile
    std::ifstream infile("data/day9.txt");
    // part 1
    int n = find_invalid(infile, 25);
    std::cout << "First invalid number: " << n << std::endl;

    // part 2
    infile.seekg(0, std::ios::beg); // re-read file
    std::vector<int> numbers = {};
    int minmax = find_seq(n, numbers, infile);
    std::cout << "Minmax: " << minmax << std::endl;
    return 0;
}