VPATH = src
objects = data-structure.o io.o main.o
demo : $(objects)
	g++ $(objects) -o demo

data-structure.o : data-structure.h src/data-structure.cpp
	g++ -c src/data-structure.cpp
main.o : data-structure.h main.cpp
	g++ -c main.cpp

clean : 
	-rm $(objects) demo