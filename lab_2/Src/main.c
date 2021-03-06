#include <stdint.h>
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
	//run while
	while(1);
}
