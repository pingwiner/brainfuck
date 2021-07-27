#pragma once

#include "x86_instruction.h"

namespace brainfuck {

	class X86end : public X86instruction {
		public:
			X86end() : X86instruction(end) {};
			size_t getSize() const override {return bin.size();}
			const uint8_t* getData() override {return bin.data();}

			void serialize(std::ofstream& out) override {
				uint16_t relAddr = 0xffff - (offset + getSize() - arg) + 1;
				bin[5] = relAddr & 0xff;
				bin[6] = relAddr >> 8;
				X86instruction::serialize(out);
			}

		private:
			std::array<uint8_t, 7> bin = {0x38, 0x1c, 0x74, 0x03, 0xe9, 0, 0};	
		
	};
}
