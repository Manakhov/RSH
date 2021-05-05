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
	RCC->CR |= RCC_CR_HSEON;
	while((RCC->CR & RCC_CR_HSERDY) == 0);
	RCC->PLLCFGR |= RCC_PLLCFGR_PLLSRC_HSE;
	// PLLM = 4
	RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLM_5;
	RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLM_4;
	RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLM_3;
	RCC->PLLCFGR |= RCC_PLLCFGR_PLLM_2;
	RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLM_1;
	RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLM_0;
	// PLLN = 350
	RCC->PLLCFGR |= RCC_PLLCFGR_PLLN_8;
	RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLN_7;
	RCC->PLLCFGR |= RCC_PLLCFGR_PLLN_6;
	RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLN_5;
	RCC->PLLCFGR |= RCC_PLLCFGR_PLLN_4;
	RCC->PLLCFGR |= RCC_PLLCFGR_PLLN_3;
	RCC->PLLCFGR |= RCC_PLLCFGR_PLLN_2;
	RCC->PLLCFGR |= RCC_PLLCFGR_PLLN_1;
	RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLN_0;
	// PLLP = 6
	RCC->PLLCFGR |= RCC_PLLCFGR_PLLP_1;
	RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLP_0;
	RCC->CR |= RCC_CR_PLLON;
	while((RCC->CR & RCC_CR_PLLRDY) == 0);

	RCC->CR &= ~RCC_CR_HSION;
	while((RCC->CR & RCC_CR_HSIRDY) == 0);

}
