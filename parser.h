#pragma once

#include "instruction.h"

namespace brainfuck {

	class Parser {
	public:
		virtual Instruction parse(char cmd) const = 0;
	};

}