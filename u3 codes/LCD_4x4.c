
#include "lpc2148.h"
#include "stdint.h"
// MKBD tested ok for both ports
//  Define all your variables here - donot use variable name as seg[]
unsigned int i, delay_ms, segval;
unsigned char index;
unsigned char lcdval, row, keyscan, keyret, keynum = 0;
// define prototypes
void InitLPC(void);
void Delay(unsigned int);
void InitLPC(void)
{
    // use the Wizards (see Wizards menu) to configure the on-chip peripherals
    // Note H1 is used for MKBD and H2 for 7 seg display for ease of programming
    PINSEL0 = 0x00L;
    IO0DIR = 0XFFFFFFF0;
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
// This is the keypress data you need to show Hex to 7Segment
unsigned char seg7[] =
    {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x67, 0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71, 0x00, 0x00, 0x00};
// This is the keyboard scan codes to output
unsigned char scan[] = {0xEF, 0xDF, 0xBF, 0x7F, 0x00};
// This is the response when user presses a key for each row
unsigned char keycode[] =
    {0xEE, 0xED, 0xEB, 0xE7, 0xDE, 0xDD, 0xDB, 0xD7, 0xBE, 0xBD, 0xBB, 0xB7, 0x7E, 0x7D, 0x7B, 0x77, 0x00};
void GetKey()
{
    row = 0;
    while (1)
    {
        IO0CLR = 0xFF;
        row &= 0x3;
        keyscan = scan[row];
        IO0SET = keyscan;
        Delay(2);
        keyret = IO0PIN;
        if (keyscan != keyret) // SCAN 4 bits = E,D,B,7
            break;             // RET is F= 1111 if nokey press else RET

        row++; // IF send E and recive F no key press
    }
    for (i = 0; i < 0x10; i++)
    {
        if (keycode[i] == keyret)
            keynum = i;
    }

    IO0CLR = 0xFF00; // Connect 7 Segment on H2 with select pin grounded
    segval = seg7[keynum];
    segval <<= 8;
    IO0SET = segval;
}
void main(void)
{
    InitLPC();
    index = 0;
    while (1)
    {
        GetKey();
    }
}