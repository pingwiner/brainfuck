#include "text_parser.h"

namespace brainfuck {

	Instruction TextParser::parse(char cmd) {
		Instruction result;	

		switch(cmd) {
			case '+':
				result.opCode = inc;
				break;
			default:
				result.opCode = nop;	
		}
		result.times = 0;
		return result;
	}

}