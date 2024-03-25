#include "Deque.h"
#include <stdlib.h>

Block* NewBlock(int sz) {
    Block *new_block = calloc(1, sizeof(Block));
    new_block->val = calloc(sz, sizeof(int));
    new_block->sz = sz;
    return new_block;
}

void DeleteBlock(Block *block) {
    free(block->val);
    free(block);
}