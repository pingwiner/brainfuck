#pragma once

#include <cstdint>
#include <cstdlib>
#include <iostream>
#include "instruction.h"
#include "parser.h"

namespace brainfuck {

	class Machine {
	public:
		Machine(const Parser& parser) : Machine(parser, std::cin, std::cout){};
		Machine(const Parser& parser, std::istream& input, std::ostream& output) : parser(parser), inputStream(input), outputStream(output)  {
			code = nullptr;
			ip = 0;
			codeSize = 0;
			dp = 0;
		};
		virtual ~Machine() {}
		void reset();
		void exec(const char* code, size_t size);
		void memDump(size_t startOffset, size_t size, std::ostream& output) const;

	private:
		static const size_t memorySize = 0x10000;

		char data[memorySize];	//data memory
		size_t dp;  			//data pointer

		const char* code;			//instruction pointer
		size_t ip;
		size_t codeSize;

		std::istream& inputStream;
		std::ostream& outputStream;
		const Parser& parser;

		void run();
		void handleInc(int times);
		void handleDec(int times);
		void handleBegin();
		void handleEnd();
		void handlePrev(int times);
		void handleNext(int times);
		void handleIn(int times);
		void handleOut(int times);
		void handleNop();
		Instruction getInstruction(char cmd);
		
	};

}