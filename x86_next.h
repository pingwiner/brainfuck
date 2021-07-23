#pragma once

#include "x86_instruction.h"

namespace brainfuck {

	class X86next : public X86instruction {
		public:
			X86next() : X86instruction(next) {};
			size_t getSize() const override {return 1;}
			const uint8_t* getData() override {return &bin[0];}
		private:
			const uint8_t bin[1] = {0x46};	
		
	};
}
