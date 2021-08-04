#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <memory>
#include <unistd.h>
#include <array>
#include "parser.h"
#include "x86_instruction.h"

namespace brainfuck {

	class Generator {
		public:
			Generator(const Parser& parser) : parser(parser) {};
			void addSrc(const std::string& source);
			void generate(std::ofstream& out);

		private:
			std::string src;
			const Parser& parser;
			std::vector<std::unique_ptr<X86instruction>> instructions;
			size_t codeSize;
			const std::array<uint8_t, 28> startup = {0x0e, 0x58, 0x05, 0, 0x10, 0x50, 0x1f, 0x50, 
				0x07, 0x33, 0xc0, 0x8b, 0xf0, 0x8b, 0xf8, 0x8b, 0xd8, 0xb9, 0, 0x80, 0xfc, 0xf3, 0xab, 
				0xe8, 0x12, 0, 0xcd, 0x20};
			const std::array<uint8_t, 8> inProc = {0xb8, 0, 0x01, 0xcd, 0x21, 0x88, 0x04, 0xc3};	
			const std::array<uint8_t, 8> outProc = {0xb8, 0, 0x02, 0x8a, 0x14, 0xcd, 0x21, 0xc3};	

			template <typename T>
			void makeInstruction(size_t arg) {
				auto instr = std::make_unique<T>();
				instr->offset = codeSize;
				instr->arg = arg;
				codeSize += instr->getSize();				
				instructions.push_back(std::move(instr));
			}

			template <typename T>
			void makeInstruction() {
				makeInstruction<T>(0);
			}

			void write(std::ofstream& out, const uint8_t* data, size_t size) {
				out.write((const char*) data, size);
			}

			const size_t inProcOffset = startup.size();
			const size_t outProcOffset = startup.size() + inProc.size();
			const uint8_t ret = 0xc3;

			void handleInc(int times);
			void handleDec(int times);
			void handleBegin();
			void handleEnd();
			void handlePrev(int times);
			void handleNext(int times);
			void handleIn(int times);
			void handleOut(int times);

	};

}