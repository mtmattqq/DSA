#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include "MyVector/MyVector.h"
#include "LinkList/LinkList.h"
#include "Exercises/R-3-1.h"
#include "Exercises/R-3-3.h"
#include "Exercises/R-3-4.h"
#include "BigInt/BigInt.h"

#define RESET "\e[0m"
#define BOLD "\e[1m"
#define UNDER_LINE "\e[4m"

#define RED "\e[0;31m"
#define GREEN "\e[0;32m"
#define YELLOW "\e[0;33m"
#define BLUE "\e[0;34m"
#define MAGENTA "\e[0;35m"
#define CYAN "\e[0;36m"
#define REDB "\e[41m"

struct Color {
    int red, green, blue;
    Color() {red = green = blue = 0;}
    Color(int r, int g, int b) {
        red = r;
        green = g;
        blue = b;
    }
};

std::ostream& operator<<(std::ostream &out, const Color &color) {
    out << "\e[38;2;" 
        << color.red << ";" << color.green << ";" << color.blue 
        << "m";
    return out;
}

inline void io_speedup() {
    std::ios::sync_with_stdio(0); std::cin.tie(0);
}

int main(int argc, char *argv[]) {
    // io_speedup();
    if(argc < 2) {
        std::cout << RED "Error: miss argument: " << Color(100, 255, 100) << "\"input file name\"" RESET << "\n";
        return -1;
    }
    
    std::ifstream in(argv[1]);
    BigInt a, b;

    while(in >> a >> b) {
        // std::cout << a << " + " << b << " = ";
        // std::cout << a + b << "\n";
        // std::cout << a << " - " << b << " = ";
        // std::cout << a - b << "\n";
        // std::cout << a << " x " << b << " = ";
        // std::cout << a * b << "\n";
        // std::cout << a << " / " << b << " = ";
        // std::cout << a / b << "\n";
        std::cout << a << " % " << b << " = ";
        std::cout << a % b << "\n";
        // std::cout << a << " to the " << b << " = ";
        // std::cout << pow(a, b) << "\n";
        std::cout << "\n";
    }
}