#include "Queue.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

Node* NewNode(int val) {
    Node *new_node = calloc(1, sizeof(Node));
    new_node->val = val;
    new_node->next = NULL;
    return new_node;
}

Node* Next(Node *now) {
    assert(now != NULL);
    return now->next;
}

void DeleteNode(Node *n) {
    free(n);
}

Queue NewQueue() {
    Queue new_queue;
    new_queue.sz = 0;
    new_queue.front = new_queue.back = NULL;
    return new_queue;
}

void Push(Queue *que, int val) {
    assert(que != NULL);
    que->sz++;
    if(que->front == NULL) {
        que->front = que->back = NewNode(val);
        return;
    }

    Node *new_node = NewNode(val);
    que->back->next = new_node;
    que->back = new_node;
}

void Pop(Queue *que) {
    assert(que != NULL);
    assert(que->front != NULL);
    Node *del = que->front;
    que->front = que->front->next;
    DeleteNode(del);
    que->sz--;
    if(que->sz == 0) que->back = NULL;
}

int Front(Queue *que) {
    assert(que != NULL);
    assert(que->front != NULL);
    return que->front->val;
}

int Back(Queue *que) {
    assert(que != NULL);
    assert(que->back != NULL);
    return que->back->val;
}

int Size(Queue *que) {
    assert(que != NULL);
    return que->sz;
}

void DeleteQueue(Queue *que) {
    assert(que != NULL);
    while(que->sz > 0) {
        Pop(que);
    }
}