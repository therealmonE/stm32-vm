#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "vm.h"
#include "main.h"
#include "usart.h"

int main(void) {
	init();
	
	while (1) {
		proceed();
	}
}

void init() {
	resetVm();
	
	__enable_irq();
	
	/* Enable port clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	/* Initialize C13 to ouput */
	GPIO_InitTypeDef ledPin;
	ledPin.GPIO_Pin = GPIO_Pin_13;
	ledPin.GPIO_Mode = GPIO_Mode_Out_PP;
	ledPin.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &ledPin);
	GPIO_SetBits(GPIOC, GPIO_Pin_13);
	
	/* Initialize A2 as TX pin */
	GPIO_InitTypeDef txPin;
	txPin.GPIO_Mode = GPIO_Mode_AF_PP;
	txPin.GPIO_Pin = GPIO_Pin_2;
	txPin.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &txPin);
	
	/* Initialize A3 as RX pin */
	GPIO_InitTypeDef rxPin;
	rxPin.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	rxPin.GPIO_Pin = GPIO_Pin_3;
	rxPin.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &rxPin);
	
	/* Initialize sound sensor */
	GPIO_InitTypeDef soundSensorPin;
	soundSensorPin.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	soundSensorPin.GPIO_Pin = GPIO_Pin_0;
	soundSensorPin.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &soundSensorPin);
	
	/* Initialize USART */
	USART_InitTypeDef usart;
	USART_StructInit(&usart);
  usart.USART_BaudRate = 9600;
  USART_Init(USART2, &usart);
	
	/* Enable USART interaptions */
  USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
	USART_ITConfig(USART2, USART_IT_TC, ENABLE);
	
	/* Startup USART */
	USART_Cmd(USART2, ENABLE);
	
	/* Enable interuptions */
	NVIC_EnableIRQ(USART2_IRQn);
	
}


