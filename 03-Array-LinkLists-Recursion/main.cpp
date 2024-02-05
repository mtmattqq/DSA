#include <iostream>
#include <algorithm>
#include "MyVector/MyVector.h"


int main(void) {
    std::ios::sync_with_stdio(0); std::cin.tie(0);

    int n;
    std::cin >> n;
    MyVector<int> student;
    for(int i{1}; i <= n; ++i) {
        int a;
        std::cin >> a;
        student.push_back(a);
    }

    std::sort(student.begin(), student.end());

    std::for_each(student.begin(), student.end(), [](int e) {
        std::cout << e << " ";
    });
    std::cout << "\n";
}