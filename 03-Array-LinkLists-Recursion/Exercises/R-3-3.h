#ifndef R_3_3
#define R_3_3

#include <vector>
using vec = std::vector<float>;
using mat = std::vector<vec>;

void transpose(mat &M) {
    int n{M.size()};
    for(int i{0}; i < n; ++i) {
        for(int j{0}; j < i; ++j) {
            std::swap(M[i][j], M[j][i]);
        }
    }
}

#endif