#include <iostream>
#include <fstream>
#include <algorithm>
#include "MyVector/MyVector.h"
#include "LinkList/LinkList.h"

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

inline void io_speedup() {
    std::ios::sync_with_stdio(0); std::cin.tie(0);
}

int main(int argc, char *argv[]) {
    // io_speedup();
    if(argc < 2) {
        std::cout << RED "Error: miss argument: " GREEN "\"input file name\"" RESET << "\n";
        return -1;
    }

    std::ifstream in(argv[1]);

    int n;
    in >> n;
    LinkList<int> list;
    
    for(int i{0}; i < n; ++i) {
        int a;
        in >> a;
        list.insert(list.begin(), a);
    }

    for(List::Node<int> *i{list.begin()}; i != list.end(); i = list.next(i)) {
        std::cout << i->val << " ";
    }
    std::cout << "\n";
}