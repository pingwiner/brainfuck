#include "generator.h"
#include "x86_inc.h"
#include "x86_dec.h"
#include "x86_prev.h"
#include "x86_next.h"

namespace brainfuck {

	void Generator::addSrc(const std::string& source) {
		src.append(source);
	}
	
	void Generator::generate(std::ofstream& output) {
		codeSize = 0;
		for(char& c : src) {
			Instruction instr = parser.parse(c);
			switch(instr.opCode) {
				case inc:
					handleInc(instr.times);
					break;
				case dec:
					handleDec(instr.times);
					break;
				case next:
					handleNext(instr.times);
					break;
				case prev:
					handlePrev(instr.times);
					break;
				case begin:
					handleBegin();
					break;
				case end:
					handleEnd();
					break;
				case in:
					handleIn(instr.times);
					break;
				case out:
					handleOut(instr.times);
					break;
				case nop:
					break;	
				default:	
					throw std::domain_error("Unknown instruction");
			}
    		
		}
	}


	void Generator::handleInc(int times) {
		while(times--) {
			auto instr = std::make_unique<X86inc>();
			instr->offset = codeSize;
			codeSize += instr->getSize();
			instructions.push_back(std::move(instr));
		}
	}

	void Generator::handleDec(int times) {
		while(times--) {
			auto instr = std::make_unique<X86dec>();
			instr->offset = codeSize;
			codeSize += instr->getSize();
			instructions.push_back(std::move(instr));
		}
	}

	void Generator::handleNext(int times) {
		while(times--) {
			auto instr = std::make_unique<X86next>();
			instr->offset = codeSize;
			codeSize += instr->getSize();
			instructions.push_back(std::move(instr));
		}
	}

	void Generator::handlePrev(int times) {
		while(times--) {
			auto instr = std::make_unique<X86prev>();
			instr->offset = codeSize;
			codeSize += instr->getSize();
			instructions.push_back(std::move(instr));
		}
	}

	void Generator::handleBegin() {
	}

	void Generator::handleEnd() {
	}

	void Generator::handleIn(int times) {
		while(times--) {
		}
	}

	void Generator::handleOut(int times) {
		while(times--) {
		}
	}


}
//			const char inc[] = {0FEh, 4};
//			const char dec[] = {0FEh, 0ch};
//			const char next[] = {46h}
//			const char prev[] = {4eh}
//			const char in[] = {0e8h, 0, 0}