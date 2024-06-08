#include <stdint.h>
#include "stm32f4xx.h"


#define GPIOAEN			(1U<<0)
#define UART1EN			(1U<<4)

#define CR1_TE			(1U<<3)
#define CR1_UE			(1U<<13)
#define SR_TXE			(1U<<7)

#define SYS_FREQ		16000000
#define ABP2_CLK		SYS_FREQ

#define UART_BAUDRATE 	115200

static void uart_set_baudrate(USART_TypeDef *UASRTx,uint32_t PeriphClk,uint32_t BaudRate);
static uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t BaudRate);

void uart1_tx_init(void);
void uart1_write(int ch);

int main(void) {

	uart1_tx_init();

	while(1){
		uart1_write('R');
	}
}



void uart1_tx_init(void) {
							// Configure uart gpio pin
	//Enable clock access to gpioa
	RCC->AHB1ENR|= GPIOAEN;

	//Set PA9 mode to alternate function mode
	GPIOA->MODER &=~(1U<<18);
	GPIOA->MODER |= (1U<<19);

	//Set PA9 alternate function type to UART_TX (AF07)
	GPIOA->AFR[0] |= (1U<<8);
	GPIOA->AFR[0] |= (1U<<9);
	GPIOA->AFR[0] |= (1U<<10);
	GPIOA->AFR[0] &= ~(1U<<11);

							// Configure uart module
	//Enable clock access to uart1
	RCC->APB2ENR |= UART1EN; // -> ???

	//Configure baudrate
	uart_set_baudrate(USART1,ABP2_CLK, UART_BAUDRATE);


	//Configure the tranfer direction
	USART1->CR1 = CR1_TE;

	// Enable uart module
	USART1->CR1 |= CR1_UE;
}

void uart1_write(int ch) {
	// Make sure the transmit data register is empty
	while(!(USART1->SR & SR_TXE)){}

	// Write to transmit data register

	USART1->DR = (ch & 0xFF);
}

static void uart_set_baudrate(USART_TypeDef *UASRTx,uint32_t PeriphClk,uint32_t BaudRate){
	UASRTx->BRR = compute_uart_bd(PeriphClk,BaudRate);
}

static uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t BaudRate){
	return ((PeriphClk + (BaudRate/2U)) / BaudRate);
}
