#pragma once

#include "x86_instruction.h"

namespace brainfuck {

	class X86prev : public X86instruction {
		public:
			X86prev() : X86instruction(prev) {};
			size_t getSize() const override {return 1;}
			const uint8_t* getData() override {return &bin[0];}
		private:
			const uint8_t bin[1] = {0x4e};	
		
	};
}
