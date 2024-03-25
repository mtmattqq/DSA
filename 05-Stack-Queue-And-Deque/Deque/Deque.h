#include <stdlib.h>

typedef struct {
    int *val;
    int sz;
} Block;

Block* NewBlock(int sz);
void DeleteBlock(Block*);

typedef struct {
    Block **val;
    int sz, chunk_size;
} Deque;

Deque NewDeque(int sz);
void PushBack();
void DeleteDeque();