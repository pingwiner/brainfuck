
#include <iostream>
#include <fstream>
#include <unistd.h>
#include "machine.h"
#include "parser.h"
#include "parser_factory.h"

using namespace brainfuck;

void execFile(const char* filename, const Parser& parser) {
	Machine machine(parser);
	std::ifstream in(filename);
	std::string contents((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
	machine.exec(contents.c_str(), contents.size());
}


int main(int argc, char *argv[]) {
	int index;
	int c;
	bool compressed = false;

	while ((c = getopt(argc, argv, "c")) != -1) {
	    switch (c) {
	      case 'c':
	        compressed = true;
	        break;
	      case '?':
			if (isprint (optopt))
	          fprintf(stderr, "Unknown option `-%c'.\n", optopt);
	        else
	          fprintf(stderr, "Unknown option character `\\x%x'.\n", optopt);
	        return 1;
	      default:
	        abort ();
	    }
	}

	std::unique_ptr<Parser> parser = ParserFactory::getParser(compressed);


	if (optind == argc) {
		std::cout << "Brainfuck interpreter" << std::endl;
		std::cout << "  Usage: bf [-c] <filename>" << std::endl;
		std::cout << "  Use flag -c for compressed files\n" << std::endl;
		return 0;
	}

	for (index = optind; index < argc; index++) {
	    execFile(argv[index], *parser);
	}


	return 0;
}