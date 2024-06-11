#include <lpc2148.h>
#include "stdint.h"
unsigned int delay_ms, led_val;
unsigned char index;
unsigned int
    mvright[] = {0x80808080, 0x40404040, 0x20202020, 0x10101010, 0x08080808, 0x04040404, 0x02020202, 0x01010101, 0x00};
void InitLPC(void)
{
    PINSEL0 = 0x00L;
    IODIR = 0xFFFFFFFF;
}
void Delay(unsigned int dms)
{
    delay_ms = dms;
    while (delay_ms > 0)
        delay_ms--;
}

int main()
{
    index = 0;
    InitLPC();
    while (1)
    {
        index &= 0x7;
        led_val = mvright[index++];
        IOSET = led_val;
        Delay(20000);
        IOCLR = 0xFFFFFFFF;
    }
    return 0;
}