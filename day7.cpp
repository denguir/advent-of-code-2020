#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <tuple>

std::string get_outer_bag(std::string line) {
    std::string delimiter = " bags contain ";
    size_t pos = line.find(delimiter);
    std::string outer_bag = line.substr(0, pos);
    return outer_bag;
}

std::vector<std::string> get_inner_bags(std::string line) {
    std::vector<std::string> vec_inner_bags;
    std::string inner_bags;
    std::string bag;

    std::string delimiter = " bags contain";
    size_t pos = line.find(delimiter) + delimiter.length();
    inner_bags = line.substr(pos, std::string::npos);
    std::istringstream iss(inner_bags);
    while (std::getline(iss, bag, ',')) {
        bag = bag.substr(1, std::string::npos);
        vec_inner_bags.push_back(bag);
    }
    return vec_inner_bags;
}


std::tuple<std::string, int> decode_bag(std::string bag) {
    std::string delimiter = " ";
    size_t pos;
    std::string token;
    int i = 0;
    int n_bags;
    std::string bag_type = "";
    
    while ((pos = bag.find(delimiter)) != std::string::npos) {
        token = bag.substr(0, pos);
        if (i == 0) {
            if (token.compare("no")) {
                n_bags = std::stoi(token);
            } else {
                n_bags = 0;
            }
        } else {
            bag_type += (token + " ");
        }
        bag.erase(0, pos + delimiter.length());
        i++;
    }
    bag_type = bag_type.substr(0, bag_type.length()-1); // one space to remove
    return std::make_tuple(bag_type, n_bags);
}

bool is_contained_bag(std::string line, std::string bag) {
    std::string delimiter = " bags contain ";
    size_t pos = line.find(delimiter);
    std::string inner_bag = line.substr(pos + delimiter.length(), std::string::npos);
    return inner_bag.find(bag) != std::string::npos;
}

int count_outer_bags(std::string bag, std::string filename, std::map<std::string, bool> &processed_bags) {
    std::ifstream infile(filename);
    std::string line;
    std::string outer_bag;
    int counter = 0;
    while (std::getline(infile, line)) {
        if (is_contained_bag(line, bag)) {
            outer_bag = get_outer_bag(line);
            if (processed_bags.find(outer_bag) == processed_bags.end()) {
                counter += (1 + count_outer_bags(outer_bag, filename, processed_bags));
                processed_bags[outer_bag] = 1;
            }
        }
    }
    return counter;
}

int count_inner_bags(std::string bag, std::string filename) {
    std::ifstream infile(filename);
    std::string line;
    std::vector<std::string> inner_bags;
    std::string bag_type;
    int counter = 0;
    int n_bags;
    
    while (std::getline(infile, line)) {
        if (get_outer_bag(line).compare(bag) == 0) {
            inner_bags = get_inner_bags(line);
            for (int i = 0; i < inner_bags.size(); ++i) {
                std::tie(bag_type, n_bags) = decode_bag(inner_bags[i]);
                counter += (n_bags * (1 + count_inner_bags(bag_type, filename)));
            }
        }
    }
    return counter;
}

int main() {
    std::map<std::string, bool> processed_bags;
    int n_outer_bags = count_outer_bags("shiny gold", "data/day7.txt", processed_bags);
    int n_inner_bags = count_inner_bags("shiny gold", "data/day7.txt");
    std::cout << "# outer bags: " <<  n_outer_bags << std::endl;
    std::cout << "# inner bags: " <<  n_inner_bags << std::endl;
    
    return 0;
}