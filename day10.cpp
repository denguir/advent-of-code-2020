#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>
#include <map>

typedef unsigned long long int uint64;

uint64 count_arrangememt(std::vector<int>& numbers, std::map<int, uint64>& arr) {
    arr.insert({0, 1});
    for (int i = 0; i < numbers.size(); ++i) {
        arr[numbers[i]] = 0;
        if (arr.find(numbers[i] - 1) != arr.end()) {
            arr[numbers[i]] += arr[numbers[i] - 1];
        }
        if (arr.find(numbers[i] - 2) != arr.end()) {
            arr[numbers[i]] += arr[numbers[i] - 2];
        } 
        if (arr.find(numbers[i] - 3) != arr.end()) {
            arr[numbers[i]] += arr[numbers[i] - 3];
        } 
    }
    return arr[numbers.back()];
}


int main() {
    std::ifstream infile("data/day10.txt");
    int jolts = 0;
    int delta1 = 0;
    int delta3 = 1;
    int delta;
    std::istream_iterator<int> start(infile), end;
    std::vector<int> numbers(start, end);
    std::sort(numbers.begin(), numbers.end());
    std::map<int, uint64> arr;

    // part 1
    for (int i=0; i<numbers.size(); i++) {
        delta = numbers[i] - jolts;
        if (delta == 1) {
            delta1++;
        } else if (delta == 3) {
            delta3++;
        }
        jolts = numbers[i];

        if (delta > 3) {
            break;
        }
    }

    std::cout << "Result: " << delta1 * delta3 << std::endl;

    // part 2
    uint64 n_arr;
    n_arr = count_arrangememt(numbers, arr);
    std::cout << "Number arrangements: " << n_arr << std::endl;
    return 0;
}