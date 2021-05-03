#include <stdint.h>

#define PERIPH_BASE 0x40000000
#define PERIPH_BB_BASE (PERIPH_BASE + 0x02000000)
#define AHB1_BASE (PERIPH_BASE + 0x00020000)
#define GPIOC_BASE (AHB1_BASE + 0x00000800)

typedef struct
{
	uint32_t MODER;
	uint32_t OTYPER;
	uint32_t OSPEEDER;
	uint32_t PUPDR;
	uint32_t IDR;
	uint32_t ODR;
	uint32_t BSRR;
	uint32_t LCKR;
	uint32_t AFRL;
	uint32_t AFRH;
} GPIO_TypeDef;

#define GPIOC ((GPIO_TypeDef *) GPIOC_BASE)


int main(void)
{
	int value = 0;
	int value_prev = 0;
	int value_blue = 0;
	int value_red = 0;
	int i = 0;
	*((uint32_t *) 0x40023830) |= 1 | 4;
	while(1)
	{
		if (GPIOC->IDR & 1 << 5)
			value++;
		    if (value > 3)
		    	value = 0;
		else if (GPIOC->IDR & 1 << 6)
			value--;
		    if (value < 0)
		    	value = 3;
        if (value != value_prev)
        	value_blue = value / 2;
        	value_red = value % 2;
        	if (value_blue)
        		GPIOC->ODR = GPIOC->ODR | 1 << 8;
        	else
        		GPIOC->ODR = GPIOC->ODR & !(1 << 8);
        	if (value_red)
        		GPIOC->ODR = GPIOC->ODR | 1 << 9;
        	else
			    GPIOC->ODR = GPIOC->ODR & !(1 << 9);
        	value_prev = value;
        	for(i = 0; i < 1000000; i++);
	}
}
