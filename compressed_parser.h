#pragma once

#include "parser.h"

namespace brainfuck {

	class CompressedParser : public Parser {
	public:
		virtual Instruction parse(char cmd) const;
	};

}