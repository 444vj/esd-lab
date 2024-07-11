#include "lpc2148.h"
#include "stdint.h"
#include "math.h"

void delay_ms(uint16_t j)
{
	uint16_t x, i;
	for (i = 0; i < j; i++)
	{
		for (x = 0; x < 6000; x++);
	}
}

unsigned int value[] = {
						511, 644, 767, 873, 954, 1006, 
						1023,
						1006, 954, 873, 767, 644, 511,
						379, 255, 149, 68, 17, 
						0,
						17, 68, 149, 255, 379
					};
int main()
{
	uint16_t val = 0, i;
	PINSEL1 = 0x00080000;
	while (1)
	{
		for (i = 0; i < 25; i++)
		{
			val = value[i];
			DACR = val << 6;
		}
	}
}

// sine alternate code
#define PI 3.1415
int main()
{
	uint16_t i;
	uint32_t val;
	PINSEL1 = 0x00080000;

	while (1)
	{
		for (i = 0; i < 550; i++)
		{
			val = 511 + 512 * sin(i*PI/180);
			DACR = val << 6;
			delay_ms(1);
		}
	}
}