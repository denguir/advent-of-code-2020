#include <iostream>
#include <fstream>
#include <tuple>


std::tuple<int, int> decode_min_max(std::string word) {
    std::string delimiter = "-";
    size_t pos = word.find(delimiter);
    int min = std::stoi(word, &pos);
    int max = std::stoi(word.substr(pos+1, std::string::npos));
    return std::make_tuple(min, max);
}


int policy1(std::string pwd, char letter, int min, int max) {
    size_t n = std::count(pwd.begin(), pwd.end(), letter);
    return n >= min && n <= max;
}


int policy2(std::string pwd, char letter, int min, int max) {
    int idx1 = min - 1;
    int idx2 = max - 1;
    return pwd[idx1] == letter ^ pwd[idx2] == letter;
}

int main() {
    std::ifstream infile("data/day2.txt");
    std::string word;

    int i = 0;
    int counter = 0;
    int min, max;
    char letter;
    std::string pwd;

    while (infile >> word) {

        if (i % 3 == 0) {
            std::tie(min, max) = decode_min_max(word);
        } else if (i % 3 == 1) {
            letter = word[0];
        } else {
            pwd = word;
            //counter += policy1(pwd, letter, min, max);
            counter += policy2(pwd, letter, min, max);
        }
        i++;
    }
    std::cout << "# correct passwords: " << counter << std::endl;
    return 0;
}