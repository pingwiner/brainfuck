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

	void Machine::exec(const char* code, size_t size) {
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
					handleNop();
					break;	
				default:	
					throw std::domain_error("Unknown instruction");
			}
		}
	}

	void Machine::handleInc(int times) {
		while(times--) data[dp]++;
	}

	void Machine::handleDec(int times) {
		while(times--) data[dp]--;
	}

	void Machine::handleNext(int times) {
		while(times--) {
			dp++;
			if (dp >= memorySize) dp = 0;
		}
	}

	void Machine::handlePrev(int times) {
		while(times--) {
			if (dp == 0) {
				dp = memorySize - 1;
			} else {
				dp--;
			}
		}
	}

	void Machine::handleBegin() {
		if (data[dp] == 0) {
			int depth = 1;
			Instruction instr;
			do {
				if (ip >= codeSize) return;
				instr = getInstruction(code[ip]);
				if (instr.opCode == OpCode::begin) depth++;
				if (instr.opCode == OpCode::end) depth--;
				ip++;
			} while((instr.opCode != OpCode::end) || (depth > 0));
		}
	}

	void Machine::handleEnd() {
		if (data[dp] == 0) return;
		ip--;
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

	void Machine::handleIn(int times) {
		while(times--) {
			inputStream.read(&data[dp], 1);
		}
	}

	void Machine::handleOut(int times) {
		while(times--) {
			outputStream.write(&data[dp], 1);
		}	
	}

	void Machine::handleNop() {}

	Instruction Machine::getInstruction(char cmd) {
		return parser.parse(cmd);
	}

	void Machine::memDump(size_t startOffset, size_t size, std::ostream& output) const {	
		if (startOffset + size > memorySize) throw std::out_of_range("Out of memory range");
		output.write(&data[startOffset], size);
	}
}
