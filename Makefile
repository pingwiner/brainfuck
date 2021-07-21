all: bf bfcompress bfc

bfc: bfc.o generator.o text_parser.o compressed_parser.o 
	g++ bfc.o generator.o text_parser.o compressed_parser.o -o bfc

bfcompress: bfcompress.o text_parser.o
	g++ bfcompress.o text_parser.o -o bfcompress

bf: main.o machine.o text_parser.o compressed_parser.o
	g++ main.o machine.o text_parser.o compressed_parser.o -o bf

bfc.o: bfc.cpp
	g++ -c bfc.cpp

generator.o: generator.cpp
	g++ -c generator.cpp

bfcompress.o: bfcompress.cpp
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
	rm -rf *.o bf bfcompress bfc