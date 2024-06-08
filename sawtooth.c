#include"lpc2148.h"
#include"stdint.h"

void delay_ms(uint16_t j)
{
	uint16_t x,i;
	for(i=0;i<j;i++){
		for(x=0;x<6000;x++);
	}
}
int main()
{
	uint16_t value=0;
	PINSEL1=0x00080000;
	while(1)
	{
		while(value!=1023)
		{
			DACR=value<<6;
			value++;
		}
		value=0;
	}
}
	