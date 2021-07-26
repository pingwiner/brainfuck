#pragma once

#include "x86_instruction.h"

namespace brainfuck {

	class X86begin : public X86instruction {
		public:
			X86begin() : X86instruction(begin) {};
			size_t getSize() const override {return 3;}
			const uint8_t* getData() override {return &bin[0];}

			void serialize(std::ofstream& out) override {

				X86instruction::serialize(out);
			}

		private:
			uint8_t bin[5] = {0, 0, 0, 0, 0};	
		
	};
}
