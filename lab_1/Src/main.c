#include <stdint.h>

#define PERIPH_BASE 0x40000000
#define PERIPH_BB_BASE (PERIPH_BASE + 0x02000000)
#define AHB1_BASE (PERIPH_BASE + 0x00020000)
#define GPIOC_BASE (AHB1_BASE + 0x00000800)

int main(void)
{
	*((uint32_t *) 0x40023830) |= 1 | 4;
	for(;;);
}
