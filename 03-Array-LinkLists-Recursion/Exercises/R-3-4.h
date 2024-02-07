#ifndef R_3_4
#define R_3_4

#include <vector>

int sum(const std::vector<std::vector<int>> &M, int i, int j) {
    if(i >= M.size()) return 0;
    if(j >= M[i].size()) return sum(M, i + 1, 0);
    return sum(M, i, j + 1) + M[i][j];
}

#endif