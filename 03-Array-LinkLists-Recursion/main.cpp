#include <iostream>
#include <algorithm>
#include "MyVector/MyVector.h"

#define NC "\e[0m"
#define RED "\e[0;31m"
#define GRN "\e[0;32m"
#define CYN "\e[0;36m"
#define REDB "\e[41m"

inline void io_speedup() {
    std::ios::sync_with_stdio(0); std::cin.tie(0);
}

int main(int argc, char *argv[]) {
    // io_speedup();
    if(argc < 2) {
        std::cout << RED "Error: need file name" NC << "\n";
    }

    for(int i{0}; i < argc; ++i) {
        std::cout << argv[i] << "\n";
    }

}