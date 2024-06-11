// Interace four 7 segment diaply to count from 0 – 9 with multiplexing.

#include <lpc2148.h>
#include <stdint.h>
#define IO1 0x10000
#define IO2 0x20000
#define IO3 0x40000
#define IO4 0x80000
#define IOX 0xF0000
#define IOXcl 0xFFFFF
// Multiplexed 7segment Display
int count = 0x0000;
unsigned int d0, d1, d2, d3;
unsigned char seg[] =
    {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x67, 0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71, 0x00};

void init_gpio()
{
    PINSEL0 = 0x00000000;
    PINSEL1 = 0x00000000;
    PINSEL2 = 0x00000000;
    IO0DIR = 0XFFFFFFFF;
    IO1DIR = 0XFFFFFFFF;
}
void delay()
{
    int c = 50000;
    while (c) // while count is more than zero loop
    {
        c--;
    }
}
void show_disp()
{
    // Digit 0
    d0 = count & 0x000F;
    IO0CLR = IOXcl;
    IO0SET = seg[d0]; // Will display data 4 on 7seg
    IO1SET = IOX;     // ALL display are OFF
    IO1CLR = IO1;     // Display1 is made on
    delay();
    IO1SET = IOX; // ALL display are OFF
    // Digit 1
    d1 = count & 0x00F0;
    d1 >>= 4;
    IO0CLR = IOXcl;
    IO0SET = seg[d1]; // Will display data 3 on 7seg
    IO1SET = IOX;     // ALL display are OFF
    IO1CLR = IO2;     // Display1 is made on
    delay();
    IO1SET = IOX; // ALL display are OFF
    // Digit 2
    d2 = count & 0x0F00;
    d2 >>= 8;
    IO0CLR = IOXcl;
    IO0SET = seg[d2]; // Willdisplay data 2 on 7seg
    IO1SET = IOX;     // ALL display are OFF
    IO1CLR = IO3;     // Display1 is made on
    delay();
    IO1SET = IOX; // ALL display are OFF
    // Digit 3
    d3 = count & 0x0F000;
    d3 >>= 12;
    IO0CLR = IOXcl;
    IO0SET = seg[d3]; // Willdisplay data 1 on 7seg
    IO1SET = IOX;     // ALL display are OFF
    IO1CLR = IO4;     // Display1 is made on
    delay();
    IO1SET = IOX; // ALL display are OFF
}
int main(void)
{
    init_gpio();
    while (1)
    {
        show_disp();
        count++;
        count &= 0xFFFF;
    }
}