#include <stdlib.h>

typedef struct {
    int *val;
    int sz;
} Block;

Block* NewBlock(int sz);
void DeleteBlock(); 

typedef struct {
    Block *val;
    int sz;
} Deque;

Deque NewDeque(int sz);
void PushBack();
void DeleteDeque();