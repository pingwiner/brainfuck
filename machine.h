#pragma once

#include <cstdint>
#include <cstdlib>
#include <iostream>
#include "instruction.h"
#include "parser.h"

namespace brainfuck {

	class Machine {
	public:
		Machine(Parser& parser) : Machine(parser, std::cin, std::cout){};
		Machine(Parser& parser, std::istream& input, std::ostream& output) : parser(parser), inputStream(input), outputStream(output)  {
			code = nullptr;
			ip = 0;
			codeSize = 0;
			dp = 0;
		};
		virtual ~Machine() {}
		void reset();
		void exec(char* code, size_t size);

	private:
		static const size_t memorySize = 0x10000;

		char data[memorySize];	//data memory
		size_t dp;  			//data pointer

		char* code;			//instruction pointer
		size_t ip;
		size_t codeSize;

		std::istream& inputStream;
		std::ostream& outputStream;
		Parser& parser;

		void run();
		void handleInc();
		void handleDec();
		void handleBegin();
		void handleEnd();
		void handlePrev();
		void handleNext();
		void handleIn();
		void handleOut();
		void handleNop();
		Instruction getInstruction(char cmd);
		
	};

}