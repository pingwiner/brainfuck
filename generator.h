#pragma once

#include <iostream>
#include <fstream>
#include "parser.h"

namespace brainfuck {

	class Generator {
		public:
			Generator(Parser& parser);
			void addSrc(const std::string& source);
			void generate(std::ofstream& out);
	};

}