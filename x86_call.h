#pragma once

#include "x86_instruction.h"

namespace brainfuck {

	class X86call : public X86instruction {
		public:
			X86call() : X86instruction(in) {};
			size_t getSize() const override {return bin.size();}
			const uint8_t* getData() override {return bin.data();}

			void serialize(std::ofstream& out) override {
				uint16_t relAddr = 0xffff - (offset + getSize() - arg) + 1;
				bin[1] = relAddr & 0xff;
				bin[2] = relAddr >> 8;
				X86instruction::serialize(out);
			}

		private:
			std::array<uint8_t, 3> bin = {0xe8, 0, 0};	
		
	};
}
