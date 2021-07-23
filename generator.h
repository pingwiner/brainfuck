#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <memory>
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