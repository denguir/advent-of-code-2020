#include <iostream>
#include <fstream>
#include <map>
#include <bitset>


void apply_mask_v1(std::string& mask, std::string& val) {
    for (int i = 0; i < mask.length(); ++i) {
        if (mask[i] != 'X') {
            val[i] = mask[i];
        }
    }
}

void apply_mask_v2(std::string& mask, std::string& addr) {
    for (int i = 0; i < mask.length(); ++i) {
        if (mask[i] != '0') {
            addr[i] = mask[i];
        }
    }
}


void floating_mem(std::string& val, std::string& addr, std::map<std::string, std::string>& mem, std::string& pre, int curr, int lvl) {

    if (curr < addr.length()) {
        if (addr[curr] == 'X') {
            pre[lvl] = '0';
            floating_mem(val, addr, mem, pre, curr + 1, lvl + 1);
            pre[lvl] = '1';
            floating_mem(val, addr, mem, pre, curr + 1, lvl + 1);
        }
        else {
            pre[lvl] = addr[curr];
            floating_mem(val, addr, mem, pre, curr + 1, lvl + 1);
        }
    } 
    else {
        pre[lvl] = '\0';
        mem[pre] = val;
    } 
}

int main() {
    std::ifstream infile("data/day14.txt");
    std::string line;
    std::string mask;
    std::string var;
    std::string val;
    std::string addr;
    std::string pre (36, 'X');
    unsigned long int temp;
    unsigned long int acc = 0;
    std::map<std::string, std::string> mem;

    while (std::getline(infile, line)) {
        var = line.substr(0, line.find(" = "));
        val = line.substr(line.find(" = ") + 3);
        if (var.compare("mask")) {
            temp = stoul(var.substr(4, var.find("]") - 1));
            addr = std::bitset<36>(temp).to_string();
            temp = stoul(val);
            val = std::bitset<36>(temp).to_string();
            
            // part 1
            // apply_mask_v1(mask, val);
            // mem[addr] = val;

            // part 2 
            apply_mask_v2(mask, addr);
            floating_mem(val, addr, mem, pre, 0, 0);

        } else {
            mask = val;
        }
    }

    for (auto const& x : mem) {
        // binary interpretation
        acc += stoul(x.second, 0, 2); 
    }

    std::cout << "Result acc: " <<  acc << std::endl;
    return 0;
}