#pragma once

#include "x86_instruction.h"

namespace brainfuck {

	class X86call : public X86instruction {
		public:
			X86call() : X86instruction(in) {};
			size_t getSize() const override {return 3;}
			const uint8_t* getData() override {return &bin[0];}

			void serialize(std::ofstream& out) override {
				*((uint16_t*) &bin[1]) = 0xffff - (offset - arg);
				X86instruction::serialize(out);
			}

		private:
			uint8_t bin[3] = {0xe8, 0, 0};	
		
	};
}
