#pragma once

#include "parser.h"

namespace brainfuck {

	class TextParser : public Parser {
	public:
		virtual Instruction parse(char cmd) const;
	};

}