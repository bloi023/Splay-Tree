all: prog2

prog2: tree.o prog2.o
	g++ -g prog2.o tree.o -o prog2

prog2.o: prog2.cpp
	g++ -g -c prog2.cpp

tree.o: tree.cpp tree.h
	g++ -g -c tree.cpp

clean:
	rm *.o prog2
