#include <iostream>
#include <fstream>
#include <sstream>
#include <map>


int main() {
    std::ifstream infile("data/day15.txt");
    std::stringstream ss;
    std::string next;
    std::map<int, int> map;
    std::map<int,int>::iterator it;

    int t = 1;
    int prev;
    int n;

    while (std::getline(infile, next, ',')) {
        n = stoi(next);
        map[n] = t;
        t++;
    }
    t--;
    map.erase(n);

    while (t < 30000000) {
        it = map.find(n);
        if (it == map.end()) {
            map[n] = t;
            n = 0;
        } else {
            prev = n;
            n = t - map[n];
            map[prev] = t;
        }
        t++;
    }
    std::cout << t << " : " << n << std::endl;
    return 0;
}