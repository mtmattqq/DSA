#include "Stack.h"
#include <stdlib.h>

Stack NewStack(int sz) {
    Stack new_stack;
    new_stack.sz = sz;
    new_stack.base = 1;
    while(new_stack.base < new_stack.sz) {
        new_stack.base <<= 1;
    }
    new_stack.val = calloc(new_stack.base, sizeof(int));
}