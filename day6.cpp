#include <iostream>
#include <fstream>
#include <sstream>
#include <map>

void clear_ans(std::map<char, int> &ans, const std::string alph) {
    for (int i=0; i < alph.length(); ++i) {
        ans[alph[i]] = 0;
    }
}

int main() {
    std::ifstream infile("data/day6.txt");
    const std::string alphabet = "abcdefghijklmnopqrstuvwxyz";
    std::string line;
    std::map<char, int> answers;
    int count = 0;
    int group_count = 0;
    
    // part 1
    // while (std::getline(infile, line)) {
    //     if (line.empty() || infile.eof()) {
    //         count += answers.size();
    //         answers.clear();
    //     } else {
    //         for (int i=0; i < line.length(); ++i) {
    //             answers[line[i]] = 1;
    //         }  
    //     }
    // }
    // // getline not reaching last line
    // count += answers.size();
    // answers.clear();
    // std::cout << "Total count: " << count << std::endl;

    // part 2
    clear_ans(answers, alphabet);
    while (std::getline(infile, line)) {
        if (line.empty() || infile.eof()) {
            for (int j=0; j < alphabet.length(); j++) {
                if (answers[alphabet[j]] == group_count) {
                    count += 1;
                }
            }
            group_count = 0;
            clear_ans(answers, alphabet);
        } else {
            group_count += 1;
            for (int i=0; i < line.length(); ++i) {
                answers[line[i]] += 1;
            }
        }
    }

    for (int j=0; j < alphabet.length(); j++) {
        if (answers[alphabet[j]] == group_count) {
            count += 1;
        }
    }

    std::cout << "Total count: " << count << std::endl;
    return 0;
}