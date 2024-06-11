// turning LED ON/OFF depending on status of PIN
#include <lpc2148.h>
#include <stdint.h>
int main(void)
{
    PINSEL0 = 0x00000000; /* Configuring P0.0 to P0.15 as GPIO */
    /* No need for this as PINSEL0 reset value is 0x
    00000000 */
    IO0DIR = 0x00000001; /* Make P0.0 bit as output bit, P0.1 bit as an in
    put pin */
    while (1)
    {
        if (IO0PIN & (1 << 1)) /* If switch is open, pin is HIGH */
        {
            IO0CLR =
                0x00000001; /* Turn on LED */
        }
        else /* If switch is closed, pin is LOW */
        {
            IO0SET =
                0x00000001; /* Turn off LED */
        }
    }
}