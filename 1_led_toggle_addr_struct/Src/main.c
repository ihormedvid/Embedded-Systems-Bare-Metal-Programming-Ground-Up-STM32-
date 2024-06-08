// Where is the led connected?
// Port: A
// Pin: 5

//APB - advanced peripheral bus вдосконалена периферійна шина
//AHP - advanced High Performance Bus ця шина є новіша
//RCC - Reset and Clock Control

#include <stdint.h>
#define PERIPH_BASE			(0x40000000UL) // the value of the address of the base address of the peripherals

// AHB1 is a high-bandwidth data bus in STM32 microcontrollers.
#define AHB1PERIPH_OFFSET	(0x00020000UL) // AHB1 is a memory bus used to connect high performance peripherals.
#define AHB1PERIPH_BASE		(PERIPH_BASE + AHB1PERIPH_OFFSET) // 0x4002 0000 serves as a starting point for working with GPIOA as well as other AHB1 peripherals.

#define GPIOA_OFFEST		(0x000U) // serves as a starting point for working with GPIOA as well as other AHB1 peripherals.
#define GPIOA_BASE			(AHB1PERIPH_BASE + GPIOA_OFFEST) // 0x40020000UL Base address GPIOA
// GPIOA_BASE = 0x40020000UL


#define RCC_OFFSET 			(0x3800UL) // access for timer
#define RCC_BASE 			(AHB1PERIPH_BASE + RCC_OFFSET) // which gives you the exact address to access and control the timers.
// RCC_BASE = 0x40023800UL

//is a data bus used in STM32 microcontrollers to connect high-bandwidth peripherals.

#define GPIOAEN 			(1U << 0)// resolution and clock synchronization


#define PIN5				(1U << 5) // Set Port A Pin 5 in mode output
#define LED_PIN				PIN5


#define __IO 				volatile

/*
 *  (1U << 10) // Set bit 10 to 1
 *  &=~(1U << 11) // Set bit 11 to 0
 */

/*
 *  The first asterisk (*) is indeed used to retrieve the value that is stored at the address pointed to by the pointer.
 *    volatile unsigned int * is the data type of the ptr pointer
 */

typedef struct {
	__IO uint32_t DUMMY[12];
	__IO uint32_t AHB1ENR; // RCC AHB1 peripheral clock register 	Address offset: 0x30

} RCC_TypeDef;

typedef struct {
	__IO uint32_t MODER; 	// GPIO port mode register			Address offset 0x00
	__IO uint32_t DUMMY[4];
	__IO uint32_t ODR; 		// GPIO port output data register 	Address offset 0x14

} GPIO_TypeDef;

#define RCC		((RCC_TypeDef*) RCC_BASE)
#define GPIOA	((GPIO_TypeDef*) GPIOA_BASE)

int main(void) {
	/* 1. Enable clock access to GPIOA */
	//RCC_AHB1EN_R |= GPIOAEN; // 0b 0000 0000 0000 0000 0000 0000 0000 1001
	RCC->AHB1ENR |= GPIOAEN;

	/* 2. Set PA5 as output pin */
//	GPIOA_MODE_R |= (1U << 10); // Set bit 10 to 1
//	GPIOA_MODE_R &=~(1U << 11); // Set bit 11 to 0

	GPIOA->MODER |= (1U << 10); // Set bit 10 to 1
	GPIOA->MODER &=~(1U << 11); // Set bit 11 to 0

	while(1) {
		/* 3. Set PA5 high */
		// GPIOA_OD_R |= LED_PIN;

		/*4. Experiment 2 : toggle PA5*/
		//GPIOA_OD_R ^= LED_PIN;

		GPIOA->ODR ^= LED_PIN;
		for(int i = 0; i < 100000; i++){}
	}
}
