#include <iostream>
#include <fstream>
#include <vector>


int main() {
    std::ifstream infile("data/day3.txt");
    std::string next_row;
    
    std::vector<int> dx = {1, 3, 5, 7, 1};
    std::vector<int> dy = {1, 1, 1, 1, 2};
    std::vector<int> x = {0, 0, 0, 0, 0};
    std::vector<int> y = {0, 0, 0, 0, 0};
    std::vector<int> n_trees = {0, 0, 0, 0, 0};

    char square;
    unsigned int result = 1;

    while (infile >> next_row) {
        for (int i=0; i < x.size(); ++i) {
            if (y[i] % dy[i] == 0) {
                square = next_row[x[i]];
                if (square == '#') {
                    n_trees[i]++;
                }
                x[i] = (x[i] + dx[i]) % next_row.length();
            }
            y[i]++;     
        }   
    }

    for (int i=0; i < x.size(); ++i) {
        result *= n_trees[i];
        std::cout << "# Tress encountered (" << dx[i] << "," << dy[i] << "): " << n_trees[i] << std::endl;
    }

    std::cout << "Product: " << result << std::endl;
    return 0;
}