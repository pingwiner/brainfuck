#include "machine.h"
#include <cstring>
#include <stdexcept>

namespace brainfuck {


	void Machine::reset() {
		std::memset(data, 0, sizeof(data));
		ip = 0;
		dp = 0;
		run();
	}

	void Machine::exec(char* code, size_t size) {
		this->code = code;
		this->codeSize = size;
		reset();
	}

	void Machine::run() {
		while (ip < codeSize) {
			char cmd = code[ip++];
			Instruction instr = getInstruction(cmd);
			switch(instr.opCode) {
				case inc:
					handleInc();
					break;
				case dec:
					handleDec();
					break;
				case next:
					handleNext();
					break;
				case prev:
					handlePrev();
					break;
				case begin:
					handleBegin();
					break;
				case end:
					handleEnd();
					break;
				case in:
					handleIn();
					break;
				case out:
					handleOut();
					break;
				case nop:
					handleNop();
					break;	
				default:	
					throw std::domain_error("Unknown instruction");
			}
		}
	}

	void Machine::handleInc() {
		data[dp]++;
	}

	void Machine::handleDec() {
		data[dp]--;
	}

	void Machine::handleNext() {
		dp++;
		if (dp >= memorySize) dp = 0;
	}

	void Machine::handlePrev() {
		if (dp == 0) {
			dp = memorySize - 1;
		} else {
			dp--;
		}
	}

	void Machine::handleBegin() {
		if (data[dp] != 0) {
			ip++;
		} else {
			int depth = 1;
			Instruction instr;
			do {
				ip++;
				if (ip >= codeSize) return;
				instr = getInstruction(code[ip]);
				if (instr.opCode == OpCode::begin) depth++;
				if (instr.opCode == OpCode::end) depth--;
			} while((instr.opCode != OpCode::end) || (depth > 0));
			ip++; 
		}
	}

	void Machine::handleEnd() {
		if (data[dp] == 0) {
			ip++;
		} else {
			int depth = 1;
			Instruction instr;
			do {
				if (ip == 0) {
					throw std::out_of_range("Instruction pointer < 0");		
				}
				ip--;
				instr = getInstruction(code[ip]);
				if (instr.opCode == OpCode::begin) depth--;
				if (instr.opCode == OpCode::end) depth++;
			} while((instr.opCode != OpCode::begin) || (depth > 0));
			ip++; 
		}
	}

	void Machine::handleIn() {
		inputStream.read(&data[dp], 1);
	}

	void Machine::handleOut() {
		outputStream.write(&data[dp], 1);
	}

	void Machine::handleNop() {
		ip++;
	}

	Instruction Machine::getInstruction(char cmd) {
		return parser.parse(cmd);
	}
}
