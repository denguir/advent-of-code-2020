#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>
#include <map>
#include <tuple>

std::tuple<bool, int> process_boot(std::vector<std::string> &instructions, std::vector<int> visited) {
    int i = 0;
    int acc = 0;
    while (i < instructions.size()) {
        if (std::find(visited.begin(), visited.end(), i) != visited.end()) {
            return std::make_tuple(1, acc); // infinite loop detected
        } else {
            visited.push_back(i);
            if (instructions[i].compare("acc") == 0) {
                acc += std::stoi(instructions[i+1]);
                i += 2;
            } else if (instructions[i].compare("jmp") == 0) {
                // *2 because instructions are in even indices
                i += (2 * (std::stoi(instructions[i+1])));
            } else {
                i += 2;
            }
        }
    }
    return std::make_tuple(0, acc);
}


int main() {
    std::ifstream infile("data/day8.txt");
    std::istream_iterator<std::string> start(infile), end;
    std::vector<std::string> instructions(start, end);
    std::vector<int> visited;
    int acc;
    bool inf = 1;
    int i = 0;
    while (inf) {
        if (instructions[i].compare("jmp") == 0) {
            instructions[i] = "nop";
            std::tie(inf, acc) = process_boot(instructions, visited);
            instructions[i] = "jmp";
        } else if (instructions[i].compare("nop") == 0){
            instructions[i] = "jmp";
            std::tie(inf, acc) = process_boot(instructions, visited);
            instructions[i] = "nop";
        }
        i+=2;
    }
    std::cout << "accumulator: " << acc << std::endl;
    return 0;
}