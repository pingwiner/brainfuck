#include <iostream>
#include <fstream>
#include <unistd.h>
#include "text_parser.h"
#include "instruction.h"

using namespace std;
using namespace brainfuck;

void flush(ofstream& out, Instruction& i) {
	if (i.times == 0) return;
	char c = (i.opCode & 7) | (i.times << 3); 
	out.write(&c, 1);
	i.times = 0;
}

void parseFile(ifstream& in, ofstream& out, TextParser& parser) {
	char c;
	Instruction i;
	i.opCode = nop;
	i.times = 0;

	while(in.get(c)) {
		Instruction tmp = parser.parse(c);
		if (tmp.opCode == nop) continue;
		if (i.opCode == tmp.opCode) {
			i.times++;
			if (i.times == 31) {
				flush(out, i);
			}
		} else {
			if (i.opCode != nop) {
				flush(out, i);
			}
			i.opCode = tmp.opCode;
			i.times = 1;
		}		
	}
	flush(out, i);
}

int main(int argc, char *argv[]) {
	int index;
	int c;
	const char* outFile = "out.cbf";

	while ((c = getopt(argc, argv, "o:")) != -1) {
	    switch (c) {
	      case 'o':
	        outFile = optarg;
	        break;
	      case '?':
			if (optopt == 'o')
          		fprintf (stderr, "Option -%c requires an argument.\n", optopt);
        	else if (isprint (optopt))
          		fprintf (stderr, "Unknown option `-%c'.\n", optopt);
        	else
          		fprintf (stderr, "Unknown option character `\\x%x'.\n", optopt);
          	return 1;
	      default:
	        abort();
	    }
	}

	ofstream out(outFile);
	TextParser parser;

	for (index = optind; index < argc; index++) {
		ifstream in(argv[index]);
	    parseFile(in, out, parser);
	}

	out.close();
	return 0;
}