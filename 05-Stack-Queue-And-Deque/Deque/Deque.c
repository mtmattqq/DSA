#include "Deque.h"
#include <stdlib.h>

Block NewBlock(int base, int id) {
    Block new_block;
    new_block.val = calloc(base, sizeof(int));
    new_block.sz = 0;
    new_block.base = base;
    return new_block;
}

void DeleteBlock(Block *block) {
    free(block->val);
}

// Return true when block is full.
bool BPushBack(Block* block, int val) {
    block->val[block->sz] = val;
    block->sz++;
    return block->sz == block->base;
}

// ----------------------------------------
// 
// Vector of Block
//
// ---------------------------------------- 
Vector NewVector() {
    Vector new_vector;
    new_vector.sz = 0;
    new_vector.base = 2;
    new_vector.array = (Block*) calloc(2, sizeof(Block));
    return new_vector;
}

void DeleteVector(Vector *vec) {
    free(vec->array);
}

void VPushBack(Vector *vec, Block val) {
    if(vec->base == vec->sz) {
        vec->base += 10;
        vec->array = (Block*) realloc((void*) vec->array, vec->base * sizeof(Block));
    }
    vec->array[vec->sz++] = val;
}

Block* VGet(Vector* vec, int index) {
    return &(vec->array[index]);
}

HashTable NewHashTable() {
    HashTable new_hash_table;
    for(int i = 0; i < DEQUE_HASH_TABLE_SIZE; ++i) {
        new_hash_table.val[i] = NewVector();
    }
    return new_hash_table;
}

int HashFunction(int id) {
    return ((id % DEQUE_HASH_TABLE_SIZE) + DEQUE_HASH_TABLE_SIZE) % DEQUE_HASH_TABLE_SIZE;
}

void HInsert(HashTable *hash_table, Block block) {
    int insert_index = HashFunction(block.id);
    for(int i = 0; i < hash_table->val[insert_index].sz; ++i) {
        if(VGet(&(hash_table->val[insert_index]), i)->id == block.id) {
            *VGet(&(hash_table->val[insert_index]), i) = block;
        }
    }
    VPushBack(&(hash_table->val[insert_index]), block);
}

Block* HGet(HashTable *hash_table, int id) {
    int get_index = HashFunction(id);
    for(int i = 0; i < hash_table->val[get_index].sz; ++i) {
        if(VGet(&(hash_table->val[get_index]), i)->id == id) {
            return VGet(&(hash_table->val[get_index]), i);
        }
    }
    return NULL;
}

void HRemove(HashTable *hash_table, int id) {
    int remove_index = HashFunction(id);
    for(int i = 0; i < hash_table->val[remove_index].sz; ++i) {
        if(VGet(&(hash_table->val[remove_index]), i)->id == id) {
            DeleteBlock(VGet(&(hash_table->val[remove_index]), i));
            return;
        }
    }
}

Deque NewDeque(int sz, int chunk_size) {
    Deque new_deque = {
        0, chunk_size, 
        0, 0, 
        0, 0,
        NewHashTable()
    };
    return new_deque;
}

void PushBack(Deque *deque, int val) {
    Block *current_block = HGet(&(deque->val), deque->back_block);
    if(current_block == NULL) {
        Block new_block = NewBlock(deque->chunk_size, deque->back_block);
        HInsert(&(deque->val), new_block);
        current_block = HGet(&(deque->val), deque->back_block);
    }
    if(BPushBack(current_block, val)) {
        deque->back_block++;
        deque->back_index = 0;
    } else {
        deque->back_index++;
    }
}

void PopBack(Deque *deque) {
    Block *current_block = HGet(&(deque->val), deque->back_block);
    if(current_block == NULL) {
        return;
    }
    current_block->val[current_block->sz] = 0;
    current_block->sz--;
    if(current_block->sz == 0) {
        HRemove(&(deque->val), current_block->id);
        deque->back_block--;
        deque->back_index = 0;
        return;
    }
    deque->back_index--;
}