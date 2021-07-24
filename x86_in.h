#pragma once

#include "x86_instruction.h"

namespace brainfuck {

	class X86in : public X86instruction {
		public:
			X86in() : X86instruction(in) {};
			size_t getSize() const override {return 3;}
			const uint8_t* getData() override {
				*((uint16_t*) &bin[1]) = 0xffff - (offset - arg);
				return &bin[0];
			}

		private:
			uint8_t bin[3] = {0xe8, 0, 0};	
		
	};
}
