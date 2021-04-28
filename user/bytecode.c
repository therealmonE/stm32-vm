#include "stm32f10x.h"
#include "bytecode.h"
#include "vm.h"

int bytecode[BYTECODE_SIZE];

void loadBytecode() {
	int bc[] = {
		ICONST, 1,
		JMPZ, 55,
		ISLOUD,
		JMPZ, 53,
		ICONST, 10,
		ICONST, 33,
		ICONST, 100,
		ICONST, 117,
		ICONST, 111,
		ICONST, 108,
		ICONST, 32,
		ICONST, 111,
		ICONST, 111,
		ICONST, 84,
		PRINT, 10,
		ICONST, 0,
		MSTORE, 0,
		MLOAD, 0,
		ICONST, 5,
		ICMPRL,
		JMPZ, 53,
		ICONST, 1000000,
		BLINK,
		ICONST, 1000000,
		DELAY,
		MLOAD, 0,
		IINC,
		MSTORE, 0,
		JMP, 33,
		JMP, 0,
		HALT
	};
	
	for (uint16_t i = 0; i < sizeof(bc); i++) {
		bytecode[i] = bc[i];
	}
}
