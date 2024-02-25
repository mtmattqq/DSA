#include "Stack.h"
#include <stdlib.h>
#include <assert.h>

Stack NewStack(int sz) {
    Stack new_stack;
    new_stack.sz = sz;
    new_stack.base = 1;
    while(new_stack.base < new_stack.sz) {
        new_stack.base <<= 1;
    }
    new_stack.val = calloc(new_stack.base, sizeof(int));
    new_stack.top = -1;
    return new_stack;
}

void Rebase(Stack* st) {
    (st->base) <<= 1;
    int *new_val = calloc(st->base, sizeof(int));
    for(int i = 0; i < st->sz; ++i) {
        new_val[i] = st->val[i];
    }
    free(st->val);
    st->val = new_val;
}

void Push(Stack *st, int val) {
    if(st->top >= st->sz) {
        st->sz++;
        if(st->sz > st->base) {
            Rebase(st);
        }
    }
    st->top++;
    st->val[st->top] = val;
}

void Pop(Stack *st) {
    assert(st->top >= 0);
    st->top--;
}

int Top(Stack *st) {
    assert(st->top >= 0);
    return st->val[st->top];
}

void Delete(Stack *st) {
    free(st->val);
}
