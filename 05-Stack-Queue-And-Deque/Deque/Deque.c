#include "Deque.h"
#include <stdlib.h>

// [left, right]
Block NewBlock(int base, int left, int right, int id) {
    Block new_block;
    new_block.val = calloc(base, sizeof(int));
    new_block.left = left;
    new_block.right = right;
    new_block.base = base;
    return new_block;
}

void DeleteBlock(Block *block) {
    if(block->base == 0) return;
    free(block->val);
    block->base = 0;
}

// Return true when block is full.
bool BPushBack(Block* block, int val) {
    if(block->right == block->base - 1) return true;
    if(block->left == block->right) {
        block->val[block->right] = val;
        return false;
    }
    block->right++;
    block->val[block->right] = val;
    return false;
}

bool BPopBack(Block *block) {
    block->val[block->right] = 0;
    block->right--;
    return block->right < block->left;
}

bool BPushFront(Block* block, int val) {
    if(block->left == 0) return true;
    if(block->left == block->right) {
        block->val[block->right] = val;
        return false;
    }
    block->left--;
    block->val[block->left] = val;
    return false;
}

bool BPopFront(Block *block) {
    block->val[block->left] = 0;
    block->left++;
    return block->left > block->right;
}

int* BGet(Block *block, int index) {
    index += block->left;
    if(index < 0 || index > block->right)
        return NULL;
    return &(block->val[index]);
}

int BSize(Block *block) {
    return block->right - block->left + 1;
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
    if(vec->base == 0) return;
    for(int i = 0; i < vec->sz; ++i) {
        DeleteBlock(&(vec->array[i]));
    }
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

void DeleteHashTable(HashTable *hash_table) {
    for(int i = 0; i < DEQUE_HASH_TABLE_SIZE; ++i) {
        DeleteVector(&(hash_table->val[i]));
    }
}

int HashFunction(int id) {
    return ((id % DEQUE_HASH_TABLE_SIZE) + DEQUE_HASH_TABLE_SIZE) % DEQUE_HASH_TABLE_SIZE;
}

void HInsert(HashTable *hash_table, Block block) {
    int insert_index = HashFunction(block.id);
    for(int i = 0; i < hash_table->val[insert_index].sz; ++i) {
        Block *current_block = VGet(&(hash_table->val[insert_index]), i);
        if(current_block->base == 0 || current_block->id == block.id) {
            *VGet(&(hash_table->val[insert_index]), i) = block;
            return;
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
    deque->sz++;
    Block *current_block = HGet(&(deque->val), deque->back_block);
    if(current_block == NULL || BPushBack(current_block, val)) {
        Block new_block = NewBlock(deque->chunk_size, 0, 0, deque->back_block);
        HInsert(&(deque->val), new_block);
        current_block = HGet(&(deque->val), deque->back_block);
        BPushBack(current_block, val);
        deque->back_index = 0;
        return;
    }
    deque->back_index++;
}

void PopBack(Deque *deque) {
    deque->sz--;
    Block *current_block = HGet(&(deque->val), deque->back_block);
    if(current_block == NULL) {
        return;
    }
    if(BPopBack(current_block)) {
        HRemove(&(deque->val), current_block->id);
        if(deque->sz == 0) {
            return;
        }
        deque->back_block--;
        deque->back_index = deque->chunk_size - 1;
        return;
    }
    deque->back_index--;
}

void PushFront(Deque *deque, int val) {
    deque->sz++;
    Block *current_block = HGet(&(deque->val), deque->front_block);
    if(current_block == NULL || BPushFront(current_block, val)) {
        Block new_block = NewBlock(
            deque->chunk_size, deque->chunk_size - 1, deque->chunk_size - 1, deque->front_block);
        HInsert(&(deque->val), new_block);
        current_block = HGet(&(deque->val), deque->front_block);
        BPushFront(current_block, val);
        deque->front_index = deque->chunk_size - 1;
        return;
    }
    deque->front_index--;
}

void PopFront(Deque *deque) {
    deque->sz--;
    Block *current_block = HGet(&(deque->val), deque->front_block);
    if(current_block == NULL) {
        return;
    }
    if(BPopFront(current_block)) {
        HRemove(&(deque->val), current_block->id);
        if(deque->sz == 0) {
            return;
        }
        deque->front_block++;
        deque->front_index = 0;
        return;
    }
    deque->front_index++;
}

void DeleteDeque(Deque *deque) {
    DeleteHashTable(&(deque->val));
}

int* DqGet(Deque *deque, int index) {
    int first_sz = BSize(HGet(&(deque->val), deque->front_block));
}