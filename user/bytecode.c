#include "stm32f10x.h"
#include "bytecode.h"
#include "vm.h"

int bytecode[BYTECODE_SIZE];

void loadBytecode() {
	int bc[] = {
		ICONST, 12,
		MSTORE, 0,
		ICONST, 1,
		MSTORE, 1,
		ICONST, 2,
		MSTORE, 2,
		MLOAD, 2,
		MLOAD, 0,
		ICONST, 1,
		IADD,
		ICMPRL,
		JMPZ, 36,
		MLOAD, 1,
		MLOAD, 2,
		IMULT,
		MSTORE, 1,
		MLOAD, 2,
		IINC,
		MSTORE, 2,
		JMP, 12,
		PRNTVAR, 0,
		PRNTCHR, 33,
		PRNTCHR, 32,
		PRNTCHR, 61,
		PRNTCHR, 32,
		PRNTVAR, 1,
		HALT

	};
	
	for (uint16_t i = 0; i < sizeof(bc); i++) {
		bytecode[i] = bc[i];
	}
}
