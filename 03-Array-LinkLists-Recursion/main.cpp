#include <iostream>
#include "MyVector/MyVector.h"

int main(void) {
    std::ios::sync_with_stdio(0); std::cin.tie(0);

    int n, m;
    std::cin >> n >> m;
    MyVector<int> student(n + 1);
    for(int i{1}; i <= n; ++i) {
        std::cin >> student[i];
    }

    for(int i{0}; i < m; ++i) {
        int index;
        std::cin >> index;
        std::cout << student[index] << "\n";
    }
}