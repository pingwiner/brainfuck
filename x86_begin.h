#pragma once

#include "x86_instruction.h"

namespace brainfuck {

	class X86begin : public X86instruction {
		public:
			X86begin() : X86instruction(begin) {};
			size_t getSize() const override {return bin.size();}
			const uint8_t* getData() override {return bin.data();}

			void serialize(std::ofstream& out) override {
				uint16_t relAddr = arg - offset;
				bin[5] = relAddr & 0xff;
				bin[6] = relAddr >> 8;
				X86instruction::serialize(out);
			}

		private:
			std::array<uint8_t, 7> bin = {0x38, 0x1c, 0x75, 0x03, 0xe9, 0, 0};
		
	};
}
