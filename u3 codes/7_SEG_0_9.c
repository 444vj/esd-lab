#include <lpc2148.h>
#include <stdint.h>
void delay(unsigned int c)
{
    unsigned int a;
    for (a = 1; a <= 60000; a++)
        ;
}
int main()
{
    PINSEL0 = 0x00000000;
    IO0DIR |= 0xffffffff;
    while (1)
    {
        int i, j, k, l;
        unsigned char a[] = {0x3f, 0x6, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x7, 0x7f, 0x6f};
        for (j = 0; j < 10; j++)
        {
            IO0SET = IO0SET | a[j];
            delay(10000);
            IO0CLR = a[j];
        } // end of for
    } // end of while
    return 0;
} // end of main