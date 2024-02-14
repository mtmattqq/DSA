#include <iostream>
#include <fstream>
#include "src/data-structure.h"

#define RESET "\e[0m"
#define RED "\e[0;41m"

int main(int argc, char *args[]) {
    if(argc < 2) {
        std::cout << RED "Error: miss argument: " << "\"input file name\"" RESET << "\n";
        return -1;
    }

    Data data;
    std::ifstream in(args[1]);

    int line{0};
    while(in >> data) {
        std::cout << "Line: " << line << "\n" << data << "\n";
        line++;
    }
}