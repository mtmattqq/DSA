typedef struct node {
    int val;
    struct node *next;
} Node;

Node* NewNode(int val);
Node* Next(Node* now);

typedef struct {
    int sz;
    Node *front, *end;
} Queue;

Queue NewQueue();
void Push(Queue *que, int val);
void Pop(Queue *que);
int Front(Queue *que);
int Back(Queue *que);
int Size(Queue *que);
void DeleteQueue();
