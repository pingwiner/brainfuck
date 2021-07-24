#pragma once

#include "x86_instruction.h"

namespace brainfuck {

	class X86out : public X86instruction {
		public:
			X86out() : X86instruction(out) {};
			size_t getSize() const override {return 3;}
			const uint8_t* getData() override {return &bin[0];}

		private:
			uint8_t bin[3] = {0xe8, 0, 0};	
		
	};
}
