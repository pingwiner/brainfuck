all: bf

bf: main.o machine.o
	g++ main.o machine.o -o bf

main.o: main.cpp
	g++ -c main.cpp

machine.o: machine.cpp
	g++ -c machine.cpp

clean:
	rm -rf *.o bf