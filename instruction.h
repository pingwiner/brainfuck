#pragma once

namespace brainfuck {

	enum OpCode {
		inc = 0,
		dec = 1,
		next = 2,
		prev = 3,
		begin = 4,
		end = 5,
		in = 6,
		out = 7,
		nop = 8
	};

	class Instruction {
		public: 

		OpCode opCode;
		int times;

	};

}