#include <iostream>
#include <iterator>
#include <fstream>
#include <vector>
#include <tuple>

int dico_search(int n, std::vector<int> &numbers, int low, int high) {
    int mid = (low + high) / 2;

    if (mid == low) {
        if (n == numbers[low] || n == numbers[high]) {
            return mid;
        } else {
            return -1; // result not found
        }    
    }

    if (n < numbers[mid]) {
        return dico_search(n, numbers, low, mid);
    } else if (n > numbers[mid]) {
        return dico_search(n, numbers, mid+1, high);
    } else {
        return mid;
    }
    return -1;
}

std::tuple<int, int, int> pair_search(int sum, std::vector<int> numbers) {
    std::sort(numbers.begin(), numbers.end());
    int a, b, prod, j;
    // apply dico search for each number 
    for (int i=0; i < numbers.size(); ++i) {
        a = numbers[i];
        j = dico_search(sum - a, numbers, 0, numbers.size()-1);
        if (j > 0 && j != i) {
            b = numbers[j];
            prod = a * b;
            return std::make_tuple(a, b, prod);
        }
    }
    return std::make_tuple(-1, -1, -1);
}

std::tuple<int, int, int, int> triplet_search(int sum, std::vector<int> numbers) {
    int a, b, c, prod, sub_sum, sub_prod;
    for (int i=0; i < numbers.size(); ++i) {
        a = numbers[i];
        sub_sum = sum - a;
        std::tie(b, c, sub_prod) = pair_search(sub_sum, numbers);
        if (sub_prod != -1) {
            prod = a * sub_prod;
            return std::make_tuple(a, b, c, prod);
        }
    }
    return std::make_tuple(-1, -1, -1, -1);
}

int main() {
    std::ifstream infile("data/day1.txt");
    std::istream_iterator<int> start(infile), end;
    std::vector<int> numbers(start, end);

    int sum = 2020;
    int prod;
    int a, b, c;

    // pair search
    std::tie(a, b, prod) = pair_search(sum, numbers);
    if (prod != -1) {
        std::cout << a << "\t" << b << std::endl;
        std::cout << "Sum = " << a + b << std::endl;
        std::cout << "Prod = " << prod << std::endl;
    } else {
        std::cout << "No pairs with sum = " << sum << " found" << std::endl;
    }

    // triplet search
    std::tie(a, b, c, prod) = triplet_search(sum, numbers);
    if (prod != -1) {
        std::cout << a << "\t" << b << "\t" << c << std::endl;
        std::cout << "Sum = " << a + b + c << std::endl;
        std::cout << "Prod = " << prod << std::endl;
    } else {
        std::cout << "No triplet with sum = " << sum << " found" << std::endl;
    }
    
    return 0;
}

