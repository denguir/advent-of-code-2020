#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <vector>
#include <tuple>
#include <regex>
#include <map>


std::tuple<std::string, std::string> get_key_value(std::string line) {
    std::string delimiter = ":";
    size_t pos = line.find(delimiter);
    std::string key = line.substr(0, pos);
    std::string value = line.substr(pos+1, std::string::npos);
    return std::make_tuple(key, value);
}

int has_fields(std::map<std::string, std::string> passport, std::vector<std::string> required_fields) {
    for (int i = 0; i < required_fields.size(); ++i) {
        if (passport.find(required_fields[i]) == passport.end()) {
            return 0;
        }
    }
    return 1;
}

bool is_valid_byr(std::map<std::string, std::string> passport) {
    int byr = std::stoi(passport["byr"]);
    return (byr >= 1920 && byr <= 2002);
}

bool is_valid_iyr(std::map<std::string, std::string> passport) {
    int iyr = std::stoi(passport["iyr"]);
    return (iyr >= 2010 && iyr <= 2020);
}

bool is_valid_eyr(std::map<std::string, std::string> passport) {
    int eyr = std::stoi(passport["eyr"]);
    return (eyr >= 2020 && eyr <= 2030);
}

bool is_valid_hgt(std::map<std::string, std::string> passport) {
    bool is_good_hgt = false;
    bool is_hgt_in = (passport["hgt"][passport["hgt"].length()-2] == 'i' && passport["hgt"][passport["hgt"].length()-1] == 'n');
    bool is_hgt_cm = (passport["hgt"][passport["hgt"].length()-2] == 'c' && passport["hgt"][passport["hgt"].length()-1] == 'm');

    if (is_hgt_in) {
        int hgt_in = std::stoi(passport["hgt"].substr(0, 2));
        is_good_hgt = (hgt_in >= 59 && hgt_in <= 76);
    } else if (is_hgt_cm) {
        int hgt_cm = std::stoi(passport["hgt"].substr(0, 3));
        is_good_hgt = (hgt_cm >= 150 && hgt_cm <= 193);
    }
    return is_good_hgt;
}

bool is_valid_hcl(std::map<std::string, std::string> passport) {
    return std::regex_match(passport["hcl"], std::regex("#([a-f,0-9]){6}"));
}

bool is_valid_ecl(std::map<std::string, std::string> passport) {
    std::vector<std::string> valid_ecl = {"amb", "blu", "brn", "gry", "grn", "hzl", "oth"};
    return std::find(valid_ecl.begin(), valid_ecl.end(), passport["ecl"]) != valid_ecl.end();

}

bool is_valid_pid(std::map<std::string, std::string> passport) {
    return std::regex_match(passport["pid"], std::regex("([0-9]){9}"));
}

int is_valid(std::map<std::string, std::string> passport, std::vector<std::string> required_fields) {
    int is_valid = 0;
    if (has_fields(passport, required_fields)) {
        bool good_byr = is_valid_byr(passport);
        bool good_iyr = is_valid_iyr(passport);
        bool good_eyr = is_valid_eyr(passport);
        bool good_hgt = is_valid_hgt(passport);
        bool good_hcl = is_valid_hcl(passport);
        bool good_ecl = is_valid_ecl(passport);
        bool good_pid = is_valid_pid(passport);
        is_valid = (good_byr && good_iyr && good_eyr && good_hgt && good_hcl && good_ecl && good_pid);
    }
    return is_valid;
}

int main() {
    std::vector<std::string> fields = {"byr", "eyr", "hgt", "iyr", "hcl", "ecl", "pid"};
    std::map<std::string, std::string> passport;

    std::ifstream infile("data/day4.txt");
    std::string next_line;
    std::string data;
    std::string k, v;
    size_t pos;
    int counter = 0;

    while(std::getline(infile, next_line)) {
        std::istringstream iss(next_line);
        if (next_line.empty() || infile.eof()) {
            // verify and moving to the next passport
            counter += is_valid(passport, fields);
            passport.clear();
        }
        else {
            while(iss >> data) {
                std::tie(k, v) = get_key_value(data);
                passport[k] = v;
            }
        }
    }
    // the last passport must be verified also
    counter += is_valid(passport, fields);
    passport.clear();

    std::cout << "# valid passports: " << counter << std::endl;
    return 0;
}