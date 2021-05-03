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
	*((uint32_t *) 0x40023830) |= 1 | 4;
	for(;;);
}
