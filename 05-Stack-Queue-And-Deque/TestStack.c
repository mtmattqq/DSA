#include <stdio.h>
#include <assert.h>
#include "Stack/Stack.h"

int main(void) {
    printf("----------------------------------------\n");
    Stack st = NewStack(10);
    Push(&st, 10);
    Push(&st, 50);
    Push(&st, 42);
    assert(Top(&st) == 42);
    Pop(&st);
    assert(Top(&st) == 50);
    for(int i = 1; i <= 100; ++i) {
        Push(&st, i * 3 + 5);
    }
    assert(Top(&st) == 100 * 3 + 5);
    printf("Successfully Tested The Stack!\n");
    printf("----------------------------------------\n");
    Delete(&st);
}