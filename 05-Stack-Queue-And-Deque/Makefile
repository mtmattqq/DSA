VPATH = Queue Stack
stack = Stack.o TestStack.o
queue = Queue.o TestQueue.o

test : $(stack) $(queue)
	gcc $(stack) -o TestStack
	./TestStack
	gcc $(queue) -o TestQueue
	./TestQueue

TestStack.o : Stack.o TestStack.c
	gcc -c -std=c99 TestStack.c

TestQueue.o : Queue.o TestQueue.c
	gcc -c -std=c99 TestQueue.c

Stack.o : Stack/Stack.c Stack/Stack.h
	gcc -c -std=c99 Stack/Stack.c

Queue.o : Queue/Queue.c Queue/Queue.h
	gcc -c -std=c99 Queue/Queue.c

clean : 
	-rm -rf *.o
	-rm -f TestStack
	-rm -f TestQueue
