#include "text_parser.h"

namespace brainfuck {

	Instruction TextParser::parse(char cmd) const {
		Instruction result;	

		switch(cmd) {
			case '+':
				result.opCode = inc;
				break;
			case '-':
				result.opCode = dec;
				break;	
			case '>':
				result.opCode = next;
				break;	
			case '<':
				result.opCode = prev;
				break;	
			case '[':
				result.opCode = begin;
				break;	
			case ']':
				result.opCode = end;
				break;	
			case '.':
				result.opCode = out;
				break;	
			case ',':
				result.opCode = in;
				break;	
			default:
				result.opCode = nop;	
		}
		result.times = 1;
		return result;
	}

}