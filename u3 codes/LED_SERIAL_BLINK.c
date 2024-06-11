#include "lpc2148.h"
void Delay(unsigned int dms);
unsigned int delay_ms, ledval, n; // Define all your variables here
void Delay(unsigned int dms)
{
    delay_ms = dms;
    while (delay_ms > 0)
    {
        delay_ms--;
    }
}
void Init_GPIO(void)
{
    PINSEL0 = 0x00000000;
    PINSEL1 = 0x00000000;
    PINSEL2 = 0x00000000;
    IO0DIR = 0XFFFFFFFF;
    IO1DIR = 0XFFFFFFFF;
}

int main()
{
    Init_GPIO();
    while (1)
    {
        for (n = 0; n < 8; n++)
        {
            switch (n)
            {
            case 0:
                ledval = 0x01010101;
                break;
            case 1:
                ledval = 0x02020202;
                break;
            case 2:
                ledval = 0x04040404;
                break;
            case 3:
                ledval = 0x08080808;
                break;
            case 4:
                ledval = 0x10101010;
                break;
            case 5:
                ledval = 0x20202020;
                break;
            case 6:
                ledval = 0x40404040;
                break;
            case 7:
                ledval = 0x80808080;
                break;
            }
            IO0CLR = 0XFFFFFFFF; // LED OFF OF PORT1 ; g_pGPIO0->IOCLR
            IO1CLR = 0XFFFFFFFF; // LED OFF OF PORT1
            Delay(10000);
            IO0SET = ledval; // TURN ON LED OF PORT0
            IO1SET = ledval; // TURN ON LED OF PORT1
            Delay(10000);
        } // end of for loop
    } // end of while loop
} // end of main