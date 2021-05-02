#include "stm32f10x.h"

#define HALT 0
#define ICONST 1
#define IADD 2
#define ISUB 3
#define IMULT 4
#define IDIV 5
#define IMOD 6
#define ICMPRL 7
#define ICMPRG 8
#define ICMPRNE 9
#define ICMPRE 10
#define LEDON 11
#define LEDOFF 12
#define BLINK 13
#define DELAY 14
#define JMP 15
#define JMPZ 16
#define MSTORE 17
#define MLOAD 18
#define IDEC 19
#define IINC 20
#define ISLOUD 21
#define PRNTCHR 22
#define PRNTVAR 23

#define STACK_SIZE 512
#define MEMORY_SIZE 512

struct Stack {
	int data[STACK_SIZE];
	int top;
};

extern struct Stack stack;
extern uint32_t ip;
extern int memory[];
extern void (*operations[]) (void);

void resetVm(void);
void push(int value);
int pop(void);
int peek(void);
int fetch(void);
void proceed(void);
void decodeAndExecute(int);

void halt(void);
void iconst(void);
void iadd(void);
void isub(void);
void imult(void);
void idiv(void);
void imod(void);
void icmprl(void);
void icmprg(void);
void icmprne(void);
void icmpre(void);
void ledon(void);
void ledoff(void);
void blink(void);
void delay(void);
void jmp(void);
void jmpz(void);
void mstore(void);
void mload(void);
void idec(void);
void iinc(void);
void isloud(void);
void prntchr(void);
void prntvar(void);
