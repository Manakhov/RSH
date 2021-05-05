#include <stdint.h>
#include "stm32f446xx.h"


#define HSE 7200000
#define PLLM 4
#define PLLN 350
#define PLLP 6
#define AHB_Prescaler 1
#define APB1_Prescaler 4
#define APB1_TimPrescaler 2
#define APB2_Prescaler 2
#define APB2_TimPrescaler 2
#define HCLK HSE/PLLM*PLLN/PLLP/AHB
#define APB1 HCLK/APB1_Prescaler
#define APB1_Tim APB1*APB1_TimPrescaler
#define APB2 HCLK/APB2_Prescaler
#define APB2_Tim APB2*APB2_TimPrescaler
#define SysTicksClk 6000
#define SysTicks HCLK/SysTicksClk


void SysTick_Handler(void)
{

}


int main(void)
{
	RCC->CR |= RCC_CR_PLLON;
	while(1)
	{
		if (RCC->CR & RCC_CR_PLLRDY)
			break;
	}
	RCC->CR |= RCC_CR_HSEON;
	while(1)
	{
		if (RCC->CR & RCC_CR_HSERDY)
			break;
	}
	RCC->CR &= ~RCC_CR_HSION;
	while(1)
	{
		if (RCC->CR & RCC_CR_HSIRDY)
			break;
	}

}
