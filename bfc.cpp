#include <iostream>
#include <fstream>
#include <unistd.h>
#include "generator.h"
#include "parser.h"
#include "parser_factory.h"

using namespace brainfuck;

void parseFile(const char* filename, Generator& generator) {
	std::ifstream in(filename);
	std::string contents((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
	generator.addSrc(contents);
}


int main(int argc, char *argv[]) {
	int index;
	int c;
	bool compressed = false;
	const char* outFile = "out.com";

	while ((c = getopt(argc, argv, "co:")) != -1) {
	    switch (c) {
	      case 'c':
	        compressed = true;
	        break;
	      case 'o':
	        outFile = optarg;
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
		std::cout << "Brainfuck compiler" << std::endl;
		std::cout << "  Usage: bfc [-c] source.bf -o out.com" << std::endl;
		std::cout << "  Use flag -c for compressed files\n" << std::endl;
		return 0;
	}

	Generator generator(*parser);

	for (index = optind; index < argc; index++) {
	    parseFile(argv[index], generator);
	}

	std::ofstream out(outFile);
	generator.generate(out);
	out.close();

	return 0;
}
