#include "lpc2148.h"
#include "stdint.h"
unsigned int cmd8[] = {0x38, 0x0E, 0x02, 0x01, 0x00};
unsigned int msg[] = {'H', 'e', 'l', 'l', 'o', 0x20, 'R', 'I', 'T', 0x20, 0x00};
unsigned int lcdval, index, delay_ms;
// define prototypes
void InitLPC(void);
void Delay(unsigned int);
void InitLPC(void)
{
    // use the Wizards (see Wizards menu) to configure the on-chip peripherals
    PINSEL0 = 0x0000;
    IO0DIR = 0XFFFFFFFF;
}

void Delay(unsigned int dms)
{
    // the timer has to work for this loop to function
    delay_ms = dms;
    while (delay_ms > 0)
    {
        delay_ms--;
    }
}
void InitLCD()
{
    index = 0;
    lcdval = cmd8[index];
    while (lcdval != 0x0)
    {
        IO0SET = lcdval;
        // Toggle E pin
        lcdval |= 0x400;
        IO0SET = lcdval;
        Delay(500);
        IO0CLR = 0xFFFF;
        index++;
        lcdval = cmd8[index];
    }
}
void ShowMsg()
{
    index = 0;
    lcdval = msg[index];
    while (lcdval != 0x0)
    {
        IO0SET = lcdval;
        // Toggle E pin
        lcdval |= 0x500;
        IO0SET = lcdval;
        Delay(500);
        IO0CLR = 0xFFFF;
        index++;
        lcdval = msg[index];
    }
}

void main(void)
{
    InitLPC();
    // use the Wizards (see Wizards menu) to configure the on-chip peripherals
    index = 0;
    while (1)
    {
        InitLCD();
        ShowMsg();
        Delay(5000);
    }
}