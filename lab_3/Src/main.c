#include <stdint.h>
#include <math.h>
#include <stdio.h>
#include "stm32f446xx.h"


#define HSE 12000000
#define PLLM 6
#define PLLN 105
#define PLLP 2
#define AHB_Prescaler 1
#define APB1_Prescaler 4
#define APB1_TimPrescaler 2
#define APB2_Prescaler 2
#define APB2_TimPrescaler 2
#define HCLK HSE/PLLM*PLLN/PLLP/AHB_Prescaler
#define APB1 HCLK/APB1_Prescaler
#define APB1_Tim APB1*APB1_TimPrescaler
#define APB2 HCLK/APB2_Prescaler
#define APB2_Tim APB2*APB2_TimPrescaler
#define SysTicksClk 6000
#define SysTicks HCLK/SysTicksClk
#define BAUDRATE 115200


void SysTick_Handler(void)
{
	static int count = 0;
	if (count > SysTicksClk)
	{
		if (GPIOC->ODR & GPIO_ODR_OD8)
			GPIOC->ODR &= ~GPIO_ODR_OD8;
		else
			GPIOC->ODR |= GPIO_ODR_OD8;
		count = 0;
	}
	count++;
}


double sin_Tailor(int value, int number)
{
	int count = 1;
	int denom = 1;
	int factor = 1;
	double sin = 0.0;
	for (count = 1; count < number; count++)
	{
		denom = denom * count;
		if (count % 2)
		{
			sin = sin + factor*(double)pow(value, count)/denom;
			factor = -factor;
		}
	}
	return sin;
}


void USART2_IRQHandler(void)
{
	static int count_receive = 0;
	static int count_transmit = 0;
	static int d = 0;
	static int i = 0;
	int value_receive = 0;
	double value_transmit = 0.0;
	char sym;
	static char result[] = "\nf(x)=**.***\r";
	if (USART2->SR & USART_SR_RXNE)
	{
		if (count_receive == 3)
			d = USART2->DR;
		else if (count_receive == 4)
		{
			i = USART2->DR;
			value_receive = d*10 + i;
			value_transmit = sin_Tailor(value_receive, 10);
			sprintf(result, "\nf(x)=%02.3f\r", value_transmit);
			USART2->CR1 |= USART_CR1_TXEIE;
		}
		else
			sym = USART2->DR;
		if (count_receive > 4)
			count_receive = 0;
		else
			count_receive++;
	}
	if (USART2->SR & USART_SR_TXE)
	{
		if (result[count_transmit] != '\0')
		{
			USART2->DR = result[count_transmit];
			count_transmit++;
		}
		else
		{
			USART2->CR1 &= ~USART_CR1_TXEIE;
			count_transmit = 0;
		}
	}
}


int main(void)
{
	// set LATENCY
	FLASH->ACR |= 3 << FLASH_ACR_LATENCY_Pos;
	// HSE on
	RCC->CR |= RCC_CR_HSEON;
	while(!(RCC->CR & RCC_CR_HSERDY));
	// select HSE
	RCC->PLLCFGR |= RCC_PLLCFGR_PLLSRC_HSE;
	// set PLLM
	RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLM;
	RCC->PLLCFGR |= PLLM << RCC_PLLCFGR_PLLM_Pos;
	// set PLLN
	RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLN;
	RCC->PLLCFGR |= PLLN << RCC_PLLCFGR_PLLN_Pos;
	// PLLP = 2
	RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLP_1;
	RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLP_0;
	// PLL on
	RCC->CR |= RCC_CR_PLLON;
	while(!(RCC->CR & RCC_CR_PLLRDY));
	// select PLL
	RCC->CFGR |= RCC_CFGR_SW_PLL;
	// AHB_Prescaler = 1
	RCC->CFGR |= RCC_CFGR_HPRE_DIV1;
	// APB1_Prescaler = 4
	RCC->CFGR |= RCC_CFGR_PPRE1_DIV4;
	// APB2_Prescaler = 2
	RCC->CFGR |= RCC_CFGR_PPRE2_DIV2;
	// run SysTick
	SysTick_Config(SysTicks);
	// GPIOC on
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
	GPIOC->MODER |= GPIO_MODER_MODER8_0;
	// GPIOA on
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	// AF MODE on
	GPIOA->MODER |= GPIO_MODER_MODER2_1;
	GPIOA->MODER |= GPIO_MODER_MODER3_1;
	GPIOA->AFR[0] |= 7 << GPIO_AFRL_AFSEL2_Pos;
	GPIOA->AFR[0] |= 7 << GPIO_AFRL_AFSEL3_Pos;
	// USART on
	RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
	// set BAUDRATE
	USART2->BRR = APB1/BAUDRATE;
	// USART2 on
	USART2->CR1 |= USART_CR1_UE;
	USART2->CR1 |= USART_CR1_TE;
	USART2->CR1 |= USART_CR1_RE;
	// interrupts on
	USART2->CR1 |= USART_CR1_RXNEIE;
	NVIC_EnableIRQ(USART2_IRQn);
	//run while
	while(1);
}
