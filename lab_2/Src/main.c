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
	RCC->CR = RCC->CR | 1 << 16;
	while(1)
	{
		if (RCC->CR & 1 << 17)
			break;
	}
	RCC->CR = RCC->CR | 0 << 0;
	while(1)
	{
		if (RCC->CR & 1 << 1)
			break;
	}
	RCC->CR = RCC->CR | 1 << 24;
	while(1)
	{
		if (RCC->CR & 1 << 25)
			break;
	}
}
