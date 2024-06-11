#include <lpc2148.h>
int delay;
int main(void)
{
    PINSEL2 = 0x00000000;
    IO1DIR = 0xFFFFFFFF; // All the pins of PORT1 are configured as Output
    while (1)
    {
        IO1SET = 0xFFFFFFFF; // Set Logic 1 to all the PORT1 pins i.e. turn on LEDs
        for (delay = 0; delay < 500000; delay++)
        {
            IO1CLR = 0xFFFFFFFF;
        }
        // Set Logic 0 to all the PORT1 pins i.e. turn off LEDs
        for (delay = 0; delay < 500000; delay++)
            ;
    }
    return 0;
}