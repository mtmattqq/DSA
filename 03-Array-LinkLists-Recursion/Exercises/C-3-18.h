#ifndef C_3_18
#define C_3_18

#include "../MyVector/MyVector.h"
#include <algorithm>

#include <iostream>

void even_greater(MyVector<int> &v, int l, int r);
void even_greater(MyVector<int> &v);
bool even(int);
bool odd(int);

bool even(int n) {
    return (n & 1 ^ 1);
}

bool odd(int n) {
    return n & 1;
}

void even_greater(MyVector<int> &v, int l, int r) {
    if(r <= l) return;
    if(even(v[l])) {
        even_greater(v, l + 1, r);
        return;
    }
    if(odd(v[r])) {
        even_greater(v, l, r - 1);
        return;
    }
    std::swap(v[l], v[r]);
    even_greater(v, l, r);
}

void even_greater(MyVector<int> &v) {
    even_greater(v, 0, v.size() - 1);
}

#endif