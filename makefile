1: main.o
	g++ -Wno-deprecated -o 1 main.o

main.o: main.cpp Teoria.h Simulacion.h Modelo.h
	g++ -c -o main.o main.cpp

clean:
	rm -rf install *.o