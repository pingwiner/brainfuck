all: bf bfcompress

bfcompress: bfcompress.o text_parser.o
	g++ bfcompress.o text_parser.o -o bfcompress

bf: main.o machine.o text_parser.o compressed_parser.o
	g++ main.o machine.o text_parser.o compressed_parser.o -o bf

bfcompress.o:
	g++ -c bfcompress.cpp

main.o: main.cpp
	g++ -c main.cpp

machine.o: machine.cpp
	g++ -c machine.cpp

text_parser.o: text_parser.cpp
	g++ -c text_parser.cpp

compressed_parser.o: compressed_parser.cpp
	g++ -c compressed_parser.cpp	

clean:
	rm -rf *.o bf bfcompress