#pragma once

#include "parser.h"
#include "text_parser.h"
#include "compressed_parser.h"
#include <memory>

namespace brainfuck {

	class ParserFactory {

	public:
		static std::unique_ptr<Parser> getParser(bool compressed) {
			if (compressed) {
				return std::make_unique<CompressedParser>();
			}

			return std::make_unique<TextParser>();
		}

	};
}