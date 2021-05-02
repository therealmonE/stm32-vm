#include "stm32f10x.h"
#include "vm.h"
#include "usart.h"
#include "bytecode.h"

uint32_t ip = 0;

int memory[MEMORY_SIZE];

void (*operations[]) (void) = {
	halt,
	iconst,
	iadd,
	isub,
	imult,
	idiv,
	imod,
	icmprl,
	icmprg,
	icmprne,
	icmpre,
	ledon,
	ledoff,
	blink,
	delay,
	jmp,
	jmpz,
	mstore,
	mload,
	idec,
	iinc,
	isloud,
	prntchr,
	prntvar
};

struct Stack stack;

void proceed() {
	if (ip < BYTECODE_SIZE) {
		int opCode = fetch();
		
		decodeAndExecute(opCode);
	}
}

void decodeAndExecute(int opCode) {
	operations[opCode]();
}

void push(int value) {
	stack.data[++stack.top] = value;
}	

int pop() {
	return stack.data[stack.top--];
}

int fetch() {
	return bytecode[ip++];
}

void halt() {
	ip = BYTECODE_SIZE;
}

void iconst() {
	push(fetch());
}

void iadd() {
	push(pop() + pop());
}

void isub() {
	int op2 = pop();
	int op1 = pop();
	push(op1 - op2);
}

void imult() {
	push(pop() * pop());
}

void idiv() {
	int op2 = pop();
	int op1 = pop();
	push(op1 / op2);
}

void imod() {
	int op2 = pop();
	int op1 = pop();
	push(op1 % op2);
}

void icmprl() {
	int op2 = pop();
	int op1 = pop();
	push(op1 < op2);
}

void icmprg() {
	int op2 = pop();
	int op1 = pop();
	push(op1 > op2);
}

void icmprne() {
	int op2 = pop();
	int op1 = pop();
	push(op1 != op2);
}

void icmpre() {
	int op2 = pop();
	int op1 = pop();
	push(op1 == op2);
}

void ledon() {
	GPIO_ResetBits(GPIOC, GPIO_Pin_13);
}

void ledoff() {
	GPIO_SetBits(GPIOC, GPIO_Pin_13);
}

void blink() {
	int delay = pop();
	ledon();
	for (int i = 0; i < delay; i++); 
	ledoff();
}

void delay() {
	int delay = pop();
	for (int i = 0; i < delay; i++);
}

void jmp() {
	ip = (uint32_t) fetch();
}

void jmpz() {
	uint32_t address = (uint32_t) fetch();
	if (pop() == 0) {
		ip = address;
	}
}

void mstore() {
	memory[(uint32_t) fetch()] = pop();
}

void mload() {
	push(memory[(uint32_t) fetch()]);
}

void idec() {
	push(pop() - 1);
}

void iinc() {
	push(pop() + 1);
}

void isloud() {
	push(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0));
}

void prntchr() {
	sendSymbol((char) fetch());
}

void prntvar() {
	int varValue = memory[fetch()];
	
	if (varValue == 0) {
		sendSymbol('0');
	} else {
		char varString[10] = {0,0,0,0,0,0,0,0,0,0};
	
		int i = 9;
		
		while (varValue != 0) {
			varString[i] = (char) (48 + (varValue % 10));
			
			varValue = varValue / 10;
			i--;
		}
		
		for (uint16_t j = 0; j < sizeof(varString); j++) {
			if (varString[j] != 0) {
				sendSymbol(varString[j]);
			}
		}
	}
}

void resetVm() {
	loadBytecode();
	stack.top = -1;
	ip = 0;
}


