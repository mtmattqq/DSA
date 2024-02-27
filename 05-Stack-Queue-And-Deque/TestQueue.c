#include <stdio.h>
#include <assert.h>
#include "Queue/Queue.h"

int main(void) {
    printf("----------------------------------------\n");
    Queue que = NewQueue();
    Push(&que, 10);
    Push(&que, 50);
    Push(&que, 42);
    assert(Front(&que) == 10 && Back(&que) == 42);
    Pop(&que);
    assert(Front(&que) == 50 && Back(&que) == 42);
    for(int i = 1; i <= 100; ++i) {
        Push(&que, i * 3 + 5);
    }
    for(int i = 0; i < 10; ++i) {
        Pop(&que);
    }
    assert(Front(&que) == 9 * 3 + 5);
    DeleteQueue(&que);
    printf("Successfully Tested The Queue!\n");
    printf("----------------------------------------\n");
}