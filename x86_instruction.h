#pragma once

#include <iostream>
#include <fstream>
#include <unistd.h>
#include "instruction.h"

namespace brainfuck {

	class X86instruction {
		public:
			X86instruction(OpCode opcode) : opCode(opcode) {}
			OpCode opCode;
			uint16_t arg;
			size_t offset;

			virtual size_t getSize() const = 0;
			virtual const uint8_t* getData() = 0;

			virtual void serialize(std::ofstream& out) {
				out.write((char*) getData(), getSize());
			}

//			const char in[] = {0e8h, 0, p0}
	};
}
