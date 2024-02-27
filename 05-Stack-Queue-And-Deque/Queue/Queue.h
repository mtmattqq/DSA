#ifndef QUEUE_H
#define QUEUE_H

typedef struct node {
    int val;
    struct node *next;
} Node;

Node* NewNode(int val);
Node* Next(Node *now);
void DeleteNode(Node *n);

typedef struct {
    int sz;
    Node *front, *back;
} Queue;

Queue NewQueue();
void Push(Queue *que, int val);
void Pop(Queue *que);
int Front(Queue *que);
int Back(Queue *que);
int Size(Queue *que);
void DeleteQueue(Queue *que);

#endif  