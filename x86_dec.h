#pragma once

#include "x86_instruction.h"

namespace brainfuck {
	class X86dec : public X86instruction {
		public:
			X86dec() : X86instruction(dec) {};

			size_t getSize() const override {
				if (arg) {
					return 6;
				} else {
					return 2;
				}
			}
			
			const uint8_t* getData() override {
				if (!arg) {
					return &bin[0];
				} else {
					return &binOptimized[0];
				}
			}
			
			void serialize(std::ofstream& out) override {
				if (arg) {
					binOptimized[3] = (uint8_t) arg;
				}
				X86instruction::serialize(out);
			}

		private:
			const uint8_t bin[2] = {0xfe, 0x0c};	
			uint8_t binOptimized[6] = {0x8a, 0x04, 0x2c, 0x0, 0x88, 0x04};
		

	};
}