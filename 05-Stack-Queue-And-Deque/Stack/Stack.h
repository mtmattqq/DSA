typedef struct stack {
    int *val;
    int sz, base, top;
} Stack;

Stack NewStack(int sz);
void Rebase(Stack*);
void Push(Stack*, int val);
void Pop(Stack*);
int Top(Stack*);
void Delete(Stack*);