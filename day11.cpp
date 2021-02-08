#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>

int ngb_occ_seats(std::vector<std::string>& seats, int i, int j) {
    int c = 0;
    for (int k = -1; k < 2; ++k) {
        for (int l = -1; l < 2; ++l) {
            if (seats[i + k][j + l] == '#') {
                c++;
            }
        }
    }
    return c;
}

bool in_map(std::vector<std::string>& seats, int i, int j) {
    bool y_in_map = i > 0 && i < seats.size() - 1;
    bool x_in_map = j > 0 && j < seats[i].length() - 1;
    return x_in_map && y_in_map;
}

int sight_occ_seats(std::vector<std::string>& seats, int i, int j) {
    int x, y;
    int c = 0;
    for (int k = -1; k < 2; ++k) {
        for (int l = -1; l < 2; ++l) {
            y = i + k;
            x = j + l;
            while(in_map(seats, y, x) && seats[y][x] == '.') {
                y += k;
                x += l;
            }
            if (seats[y][x] == '#') {
                c++;
            }
        }
    }
    return c;
}

int occ_seats(std::vector<std::string>& seats) {
    int c = 0;
    for (int i = 1; i < seats.size() - 1; ++i) {
        for (int j = 1; j < seats[i].length() - 1; ++j) {
            if (seats[i][j] == '#') {
                c++;
            }
        }
    }
    return c;
}

void update_part1(std::vector<std::string>& seats, std::vector<std::string>& state) {
    for (int i = 1; i < seats.size() - 1; ++i) {
        for (int j = 1; j < seats[i].length() - 1; ++j) {
            if (state[i][j] == 'L') {
                if (ngb_occ_seats(state, i, j) == 0) {
                    seats[i][j] = '#';
                }
            }
            if (state[i][j] == '#') {
                if (ngb_occ_seats(state, i, j) > 4) {
                    seats[i][j] = 'L';
                }
            }
        }
    }
}

void update_part2(std::vector<std::string>& seats, std::vector<std::string>& state) {
    for (int i = 1; i < seats.size() - 1; ++i) {
        for (int j = 1; j < seats[i].length() - 1; ++j) {
            if (state[i][j] == 'L') {
                if (sight_occ_seats(state, i, j) == 0) {
                    seats[i][j] = '#';
                }
            }
            if (state[i][j] == '#') {
                if (sight_occ_seats(state, i, j) > 5) {
                    seats[i][j] = 'L';
                }
            }
        }
    }
}

void pad(std::vector<std::string>& seats) {
    std::string corner;
    for (int i = 0; i < seats.size(); ++i) {
        seats[i] = "." + seats[i] + ".";
    }
    corner = std::string(seats[0].length(), '.');
    seats.insert(seats.begin(), corner);
    seats.insert(seats.end(), corner);
}

void unpad(std::vector<std::string>& seats) {
    seats.erase(seats.end());
    seats.erase(seats.begin());
    size_t start_pos = 1;
    size_t end_pos = seats[0].length() - 2;
    for (int i = 0; i < seats.size(); ++i) {
        seats[i] = seats[i].substr(start_pos, end_pos);
    }
}

int main() {
    std::ifstream infile("data/day11.txt");
    std::istream_iterator<std::string> start(infile), end;
    std::vector<std::string> seats(start, end);
    std::vector<std::string> state;
    pad(seats);

    while (1) {
        state = seats;
        //update_part1(seats, state);
        update_part2(seats, state);

        if (state == seats) {
            std::cout << "# occupied seats: " << occ_seats(seats) << std::endl;
            break;
        }
    }
    return 0;
}