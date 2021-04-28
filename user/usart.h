#define USART_BUFFER_SIZE 512

extern int rx;
extern char usartBuffer[];
extern short usartBufferPointer;

void USART2_IRQHandler(void);
void executeCommand(void);
void sendMessage(char message[]);
void sendSymbol(char symbol);
