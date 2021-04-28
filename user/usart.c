#include "stm32f10x.h"
#include "usart.h"
#include "stm32f10x_usart.h"
#include <string.h>
#include "vm.h"

int rx;
char usartBuffer[USART_BUFFER_SIZE];
short usartBufferPointer;

void USART2_IRQHandler() {
  //Receive Data register not empty interrupt
  if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET) {
		if (!rx) {
			rx = 1;
			usartBufferPointer = 0;
		}
	
		char data = (char) USART_ReceiveData(USART2);
		
		if (data != '$') {
			usartBuffer[usartBufferPointer++] = data;
		} else {
			rx = 0;
			usartBufferPointer = 0;
			executeCommand();
		}
		
		USART_ClearITPendingBit(USART2, USART_IT_RXNE);
  }
	
	if(USART_GetITStatus(USART2, USART_IT_TC) != RESET) {
		USART_ClearITPendingBit(USART2, USART_IT_TC);
	}
}

void executeCommand() {	
	if (strcmp(usartBuffer, "hard reset") == 0) {
		NVIC_SystemReset();
	}
	
	if (strcmp(usartBuffer, "soft reset") == 0) {
		resetVm();
	}
	
	memset(usartBuffer, 0, sizeof(usartBuffer));
}

void sendMessage(char message[]) {
	for (uint16_t i = 0; i < strlen(message); i++) {
		sendSymbol(message[i]);
	}
}

void sendSymbol(char symbol) {
	USART_SendData(USART2, symbol);
	while(!(USART2->SR & USART_SR_TXE));
}
