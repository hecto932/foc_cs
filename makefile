1: main.o
	g++ -Wno-deprecated -o 1 main.o

main.o: main.cpp libraries/Teoria.h libraries/Simulacion.h libraries/Modelo.h
	g++ -c -o main.o main.cpp

clean:
	rm -rf install *.o