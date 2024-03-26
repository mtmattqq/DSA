#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int *val;
    int sz, id, base;
} Block;

Block NewBlock(int base, int id);
bool BPushBack(Block* block, int val);
void DeleteBlock(Block*);

typedef struct {
    int64_t sz, base;
    Block *array;
} Vector;

Vector NewVector();
void DeleteVector(Vector*);
void Resize(Vector*, Block);
void VPushBack(Vector*, Block);
Block* VGet(Vector*, int index);

#define DEQUE_HASH_TABLE_SIZE 1024

typedef struct {
    Vector val[DEQUE_HASH_TABLE_SIZE];
} HashTable;

HashTable NewHashTable();
void HInsert(HashTable *hash_table, Block block);
Block* HGet(HashTable *hash_table, int id);
void HRemove(HashTable *hash_table, int id);

typedef struct {
    int sz, chunk_size;
    int front_block, front_index;
    int back_block, back_index;
    HashTable val;
} Deque;

Deque NewDeque(int sz, int chunk_size);
void PushBack(Deque *deque, int val);
void PopBack(Deque *deque);
void PushFront(Deque *deque, int val);
void PopFront(Deque *deque);
void DeleteDeque(Deque *dq);