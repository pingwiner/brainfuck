#include "generator.h"
#include "x86_inc.h"
#include "x86_dec.h"
#include "x86_prev.h"
#include "x86_next.h"
#include "x86_in.h"
#include "x86_out.h"

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
			makeInstruction<X86inc>();
		}
	}

	void Generator::handleDec(int times) {
		while(times--) {
			makeInstruction<X86dec>();
		}
	}

	void Generator::handleNext(int times) {
		while(times--) {
			makeInstruction<X86next>();
		}
	}

	void Generator::handlePrev(int times) {
		while(times--) {
			makeInstruction<X86prev>();
		}
	}

	void Generator::handleBegin() {
	}

	void Generator::handleEnd() {
	}

	void Generator::handleIn(int times) {
		while(times--) {
			makeInstruction<X86in>(inProcOffset);
		}
	}

	void Generator::handleOut(int times) {
		while(times--) {
			makeInstruction<X86out>(outProcOffset);
		}
	}


}
