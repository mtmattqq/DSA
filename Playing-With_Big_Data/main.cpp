#include <iostream>
#include <fstream>
#include <string>
#include "src/data-structure.h"

#define RESET "\e[0m"
#define RED "\e[0;41m"

int main(int argc, char *args[]) {
    if(argc < 2) {
        std::cout << RED "Error: miss argument: " RESET "\"input file name\"" << "\n";
        return -1;
    }

    std::ifstream in(args[1]);
    Data data;
    DataStructure all_data;

    int64_t progress{0}, max_progress = 15000000;
    while(in >> data) {
        all_data.insert(data);
        progress++;
        if(progress % 300000 == 0) {
            std::cerr << "[";
            int len{0};
            for(int64_t i{0}; i * 300000 < progress; ++i) {
                std::cerr << "=";
                len++;
            }
            for(int i{0}; i + len < 50; ++i) {
                std::cerr << " ";
            }
            std::cerr << "] " << double(progress) * 100.0 / max_progress << "%\r";
        }
    }
    std::cerr << "\n";

    std::string op, u, p, p1;
    while(std::cin >> op) {
        if(op == "quit") break;
        if(op == "get") {
            int64_t t;
            std::cin >> u >> p >> t;
            all_data.get(u, p, t);
        } else if(op == "purchased") {
            std::cin >> u;
            all_data.purchased(u);
        } else if(op == "clicked") {
            std::cin >> p >> p1;
            all_data.clicked(p, p1);
        } else if(op == "profit") {
            int64_t t;
            double rate;
            std::cin >> t >> rate;
            all_data.profit(t, rate);
        }
    }
}