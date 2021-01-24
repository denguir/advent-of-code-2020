#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

int decode_seat_id(std::string seat) {
    std::string row = seat.substr(0, 7);
    std::string col = seat.substr(7, std::string::npos);

    int row_n, col_n, seat_id;
    // binarize row number
    std::replace(row.begin(), row.end(), 'F', '0');
    std::replace(row.begin(), row.end(), 'B', '1');
    row_n = std::stoi(row, nullptr, 2);

    // binarize col number
    std::replace(col.begin(), col.end(), 'L', '0');
    std::replace(col.begin(), col.end(), 'R', '1');
    col_n = std::stoi(col, nullptr, 2);

    seat_id = row_n * 8 + col_n;
    return seat_id;
}

int main() {
    std::ifstream infile("data/day5.txt");
    std::string seat;
    std::vector<int> all_seats;
    int seat_id;
    int max_seat_id = 0;

    while (infile >> seat) {
        seat_id = decode_seat_id(seat);
        all_seats.push_back(seat_id);
        if (seat_id > max_seat_id) {
            max_seat_id = seat_id;
        }
    }

    std::sort(all_seats.begin(), all_seats.end());
    for (int i = 1; i < all_seats.size(); ++i) {
        if (all_seats[i] == all_seats[i-1] + 2) {
            seat_id = all_seats[i] - 1;
            break;
        }
    }
    std::cout << "Max seat id: " << max_seat_id << std::endl;
    std::cout << "My seat id is: " << seat_id << std::endl;
    return 0;
}