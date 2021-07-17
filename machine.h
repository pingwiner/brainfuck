#include <cstdint>
#include <cstdlib>
#include <iostream>
#include "instruction.h"

namespace brainfuck {

	class Machine {
	public:
		Machine() : Machine(std::cin, std::cout){};
		Machine(std::istream& input, std::ostream& output) : inputStream(input), outputStream(output){
			code = nullptr;
			ip = 0;
			codeSize = 0;
			dp = 0;
		};
		virtual ~Machine() {}
		void reset();
		void exec(uint8_t* code, size_t size);

	private:
		static const size_t memorySize = 0x10000;

		char data[memorySize];	//data memory
		size_t dp;  			//data pointer

		uint8_t* code;			//instruction pointer
		size_t ip;
		size_t codeSize;

		std::istream& inputStream;
		std::ostream& outputStream;

		void run();
		void handleInc();
		void handleDec();
		void handleBegin();
		void handleEnd();
		void handlePrev();
		void handleNext();
		void handleIn();
		void handleOut();
		Instruction getInstruction(uint8_t cmd);
		
	};

}