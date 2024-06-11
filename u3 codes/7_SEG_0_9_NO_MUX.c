// Interace four 7 segment display to count from 0 – 9 without multiplexing.

#include <lpc2148.h>
#include <stdint.h>

void delay(unsigned int c)
{
    unsigned int a;
    for (a = 1; a <= 60000; a++);
}
int main()
{
    PINSEL0 = 0x00000000;
    PINSEL1 = 0x00000000;
    PINSEL2 = 0x00000000;
    IO0DIR |= 0xffffffff;
    IO1DIR |= 0xffffffff;
    while (1)
    {
        int i, j, k, l;
        unsigned char a[] = {0x3f, 0x6, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x7, 0x7f, 0x6f};

        for (j = 0; j < 10; j++)
        {
            IO0SET = IO0SET | a[j]; // 4
            for (i = 0; i < 10; i++)
            { // 3
                IO0SET = IO0SET | (a[i] << 8);
                for (k = 0; k <= 9; k++)
                { // 2
                    IO0SET = IO0SET | (a[k] << 16);
                    for (l = 0; l <= 9; l++)
                    { // 1
                        IO1SET = IO1SET | (a[l] << 16);
                        delay(1000);
                        IO1CLR = IO1CLR | (a[l] << 16);
                    } // 1
                    IO0CLR = IO0CLR | (a[k] << 16);
                } // 2
                IO0CLR = IO0CLR | (a[i] << 8);
            } // 3
            IO0CLR = a[j];
        } // 4
    } // END OF WHILE
} // END OF MAIN