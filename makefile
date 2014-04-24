1: main.o
	g++ -Wno-deprecated -o 1 Teoria.cpp main.o

main.o: main.cpp
	g++ -c -o main.o main.cpp
