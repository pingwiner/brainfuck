#include "generator.h"
#include "x86_inc.h"
#include "x86_dec.h"
#include "x86_prev.h"
#include "x86_next.h"
#include "x86_call.h"
#include "x86_begin.h"
#include "x86_end.h"

namespace brainfuck {

	void Generator::addSrc(const std::string& source) {
		src.append(source);
	}
	
	void Generator::generate(std::ofstream& output) {
		write(output, startup.data(), startup.size());
		write(output, inProc.data(), inProc.size());
		write(output, outProc.data(), outProc.size());

		codeSize = startup.size() + inProc.size() + outProc.size();

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

    	std::vector<int> stack;
    	int position = 0;
		for(auto const& i : instructions) {
			if (i->opCode == begin) {
				stack.push_back(position);
			}
			if (i->opCode == end) {
				int prevPosition = stack.back();
				stack.pop_back();
				i->arg = instructions[prevPosition]->offset + instructions[prevPosition]->getSize();
				instructions[prevPosition]->arg = i->offset + i->getSize();
			}
			position++;
		}

		for(auto const& i : instructions) {
			i->serialize(output);
		}
		output.write((const char*) &ret, 1); 
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
		makeInstruction<X86begin>();
	}

	void Generator::handleEnd() {
		makeInstruction<X86end>();
	}

	void Generator::handleIn(int times) {
		while(times--) {
			makeInstruction<X86call>(inProcOffset);
		}
	}

	void Generator::handleOut(int times) {
		while(times--) {
			makeInstruction<X86call>(outProcOffset);
		}
	}


}
