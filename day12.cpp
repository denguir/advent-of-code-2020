#include <iostream>
#include <fstream>
#include <tuple>
#include <cmath>

#define PI 3.14159265

std::tuple<char, float> extract_cmd(std::string cmd) {
    char order;
    float value;
    order = cmd[0];
    value = std::stof(cmd.substr(1, std::string::npos));
    return std::make_tuple(order, value);
}

void update_pos_part1(std::string cmd, float& east, float& north, float& dir_east, float& dir_north) {
    char order;
    float value;
    std::tie(order, value) = extract_cmd(cmd);
    if (order == 'F') {
        east += (dir_east * value);
        north += (dir_north * value);
    } else if (order == 'N') {
        north += value;
    } else if (order == 'S') {
        north -= value;
    } else if (order == 'E') {
        east += value;
    } else if (order == 'W') {
        east -= value;
    } else if (order == 'L') {
        float angle = value * PI / 180.0;
        float tmp_dir_east = cos(angle) * dir_east - sin(angle) * dir_north;
        float tmp_dir_north = sin(angle) * dir_east + cos(angle) * dir_north;
        dir_east = round(tmp_dir_east);
        dir_north = round(tmp_dir_north);
    } else if (order == 'R') {
        float angle = - value * PI / 180.0;
        float tmp_dir_east = cos(angle) * dir_east - sin(angle) * dir_north;
        float tmp_dir_north = sin(angle) * dir_east + cos(angle) * dir_north;
        dir_east = round(tmp_dir_east);
        dir_north = round(tmp_dir_north);
    }
}

void update_pos_part2(std::string cmd, float& east, float& north, float& dir_east, float& dir_north) {
    char order;
    float value;
    std::tie(order, value) = extract_cmd(cmd);
    if (order == 'F') {
        east += (dir_east * value);
        north += (dir_north * value);
    } else if (order == 'N') {
        dir_north += value;
    } else if (order == 'S') {
        dir_north -= value;
    } else if (order == 'E') {
        dir_east += value;
    } else if (order == 'W') {
        dir_east -= value;
    } else if (order == 'L') {
        float angle = value * PI / 180.0;
        float tmp_dir_east = cos(angle) * dir_east - sin(angle) * dir_north;
        float tmp_dir_north = sin(angle) * dir_east + cos(angle) * dir_north;
        dir_east = round(tmp_dir_east);
        dir_north = round(tmp_dir_north);
    } else if (order == 'R') {
        float angle = - value * PI / 180.0;
        float tmp_dir_east = cos(angle) * dir_east - sin(angle) * dir_north;
        float tmp_dir_north = sin(angle) * dir_east + cos(angle) * dir_north;
        dir_east = round(tmp_dir_east);
        dir_north = round(tmp_dir_north);
    }
}


int main() {
    std::ifstream infile("data/day12.txt");
    std::string cmd;
    float north, east = 0.0;
    float dir_east = 10.0; // 1.0 in part 1
    float dir_north = 1.0;  // 0.0 in part 1
    while (infile >> cmd) {
        // update_pos_part1(cmd, east, north, dir_east, dir_north);
        update_pos_part2(cmd, east, north, dir_east, dir_north);
    }

    std::cout << "Manhattan distance: " << abs(north) + abs(east) << std::endl; 

}