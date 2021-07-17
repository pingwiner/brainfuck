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

	void Machine::exec(uint8_t* code, size_t size) {
		this->code = code;
		this->codeSize = size;
		reset();
	}

	void Machine::run() {
		while (ip < codeSize) {
			uint8_t cmd = code[ip++];
			Instruction instr = getInstruction(cmd);
			switch(instr) {
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
			do {
				ip++;
				if (ip >= codeSize) return;
				Instruction instr = getInstruction(code[ip]);
				if (instr == Instruction::begin) depth++;
				if (instr == Instruction::end) depth--;
			} while((getInstruction(code[ip]) != Instruction::end) || (depth > 0));
			ip++; 
		}
	}

	void Machine::handleEnd() {
		if (data[dp] == 0) {
			ip++;
		} else {
			int depth = 1;
			do {
				if (ip == 0) {
					throw std::out_of_range("Instruction pointer < 0");		
				}
				ip--;
				Instruction instr = getInstruction(code[ip]);
				if (instr == Instruction::begin) depth--;
				if (instr == Instruction::end) depth++;
			} while((getInstruction(code[ip]) != Instruction::begin) || (depth > 0));
			ip++; 
		}
	}

	void Machine::handleIn() {
		inputStream.read(&data[dp], 1);
	}

	void Machine::handleOut() {
		outputStream.write(&data[dp], 1);
	}

	Instruction Machine::getInstruction(uint8_t cmd) {
		return static_cast<Instruction>(cmd & 7);
	}
}
