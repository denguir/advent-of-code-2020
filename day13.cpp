#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <tuple>

typedef unsigned long long int uint64;

std::tuple<uint64, uint64> get_next_bus(std::vector<uint64>& busno, uint64 ts) {
    uint64 mod, div;
    uint64 dt;
    uint64 next_bus;
    uint64 min_dt = 0xFFFFFFFFFFFFFFFF; // 2^64 - 1 is max uint64
    for (int i = 0; i < busno.size(); ++i) {
        mod = ts % busno[i];
        div = ts / busno[i];
        if (mod == 0) {
            min_dt = 0;
            next_bus = busno[i];
            break;
        } else {
            dt = (div + 1) * busno[i] - ts;
            if (dt < min_dt) {
                min_dt = dt;
                next_bus = busno[i];
            }
        }
    }
    return std::make_tuple(next_bus, min_dt);
}

uint64 invmod(uint64 u, uint64 v) {
    // extended Euclide algorithm, computes the inverse of
    // u mod v by solving u * u^-1 mod v = 1
    // without using any negative number
    // see: https://www.di-mgt.com.au/euclidean.html
    uint64 inv, u1, u3, v1, v3, t1, t3, q;
    int iter;
    /* Step X1. Initialise */
    u1 = 1;
    u3 = u;
    v1 = 0;
    v3 = v;
    /* Remember odd/even iterations */
    iter = 1;
    /* Step X2. Loop while v3 != 0 */
    while (v3 != 0)
    {
        /* Step X3. Divide and "Subtract" */
        q = u3 / v3;
        t3 = u3 % v3;
        t1 = u1 + q * v1;
        /* Swap */
        u1 = v1; v1 = t1; u3 = v3; v3 = t3;
        iter = -iter;
    }
    /* Make sure u3 = gcd(u,v) == 1 */
    if (u3 != 1)
        return 0;   /* Error: No inverse exists */
    /* Ensure a positive result */
    if (iter < 0)
        inv = v - u1;
    else
        inv = u1;
    return inv;
}


uint64 crt(std::vector<uint64>& m, std::vector<uint64>& a) {
    // applies the chinese remainder theorem to solve the system
    // x mod mi = ai, for i=0,...,n
    uint64 M = 1;
    uint64 Mi, yi;
    uint64 res = 0;
    for (int i = 0; i < m.size(); ++i) {
        M *= m[i];
    }
    for (int i = 0; i < m.size(); ++i) {
        Mi = M / m[i];
        yi = invmod(Mi, m[i]);
        res += (a[i] * Mi * yi) % M;
    }
    res %= M;
    return res;
}

uint64 seq_ts(std::vector<uint64>& busno, std::vector<uint64>& busidx) {
    std::vector<uint64> a;
    uint64 ai;
    uint64 ts;
    for (int i = 0; i < busno.size(); ++i) {
        ai = (busno[i] - (busidx[i] % busno[i])) % busno[i]; //((-busidx[i]) % busno[i] + busno[i]) % busno[i];
        a.push_back(ai);
        // std::cout << "\nidi = " << busidx[i] << std::endl;
        // std::cout << "\nmi = " << busno[i] << std::endl;
        // std::cout << "\nai = " << ai << std::endl;
    }
    ts = crt(busno, a);
    return ts;
}

int main() {
    std::ifstream infile("data/day13.txt");
    std::stringstream ss;
    std::string line;
    std::string bus;
    std::vector<uint64> busno;
    std::vector<uint64> busidx;
    uint64 next_bus;
    uint64 dt;
    uint64 ts;
    uint64 i, j = 0;
    while(infile >> line) {
        if (i % 2 == 0) {
            ts = std::stoull(line);
        } else {
            ss.clear();
            ss.str(line);
            while(std::getline(ss, bus, ',')) {
                if (bus.compare("x")) {
                    busno.push_back(std::stoull(bus));
                    busidx.push_back(j);
                }
                j++;
            }
        }
        i++;
    }
    std::tie(next_bus, dt) = get_next_bus(busno, ts);
    std::cout << "Result part1: " << next_bus * dt << std::endl;
    std::cout << "Result part2: " << seq_ts(busno, busidx) << std::endl;
    return 0;
}