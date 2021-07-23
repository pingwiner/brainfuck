#pragma once

#include "x86_instruction.h"

namespace brainfuck {

	class X86inc : public X86instruction {
		public:
			X86inc() : X86instruction(inc) {};
			size_t getSize() const override {return 2;}
			const uint8_t* getData() override {return &bin[0];}

		private:
			const uint8_t bin[2] = {0xfe, 4};	
		
	};
}
