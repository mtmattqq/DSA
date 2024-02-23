typedef struct stack {
    int *val;
    int sz, base;
} Stack;

Stack NewStack(int sz);
void Push(Stack*);
void Pop(Stack*);
int Top(Stack*);