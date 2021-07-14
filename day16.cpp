#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <tuple>


int get_error_rate(int n, std::vector<std::tuple<int, int>>& ranges) {
    int min, max;
    int res = n;
    bool in_range = 0;
    for (std::size_t i = 0; i < ranges.size(); ++i) {
        std::tie(min, max) = ranges[i];
        in_range = in_range || (n >= min && n <= max);
    }
    if (in_range) {
        res = 0;
    }
    return res;
}


int main() {
    std::ifstream infile("data/day16.txt");
    std::istringstream iss;
    std::string line;
    std::string data;
    std::vector<std::tuple<int, int>> ranges;

    std::size_t del;
    bool is_ticket = false;
    int er = 0;
    int n;
    int min;
    int max;

    while (infile >> line) {
        del = line.find("-");
        if (del != std::string::npos) {
            min = stoi( line.substr(0, del) );
            max = stoi( line.substr(del+1 , std::string::npos) );
            ranges.push_back( std::make_tuple(min, max) );
            std::cout << min << " : " << max << std::endl;
        }

        if (is_ticket) {
            iss.clear();
            iss.str(line);
            while(std::getline(iss, data, ',')) {
                n = stoi(data);
                er += get_error_rate(n, ranges);
            }
        }

        if (line.compare("tickets:") == 0) {
            is_ticket = true;
        }
    }

    std::cout << "Error rate :" << er << std::endl;

    return 0;
}