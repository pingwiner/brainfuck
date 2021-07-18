#include "compressed_parser.h"

namespace brainfuck {

	Instruction CompressedParser::parse(char cmd) const {
		Instruction result;
		result.opCode = static_cast<OpCode>(cmd & 7);
		result.times = (cmd >> 3) & 31;
		return result;
	}

}