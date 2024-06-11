#include "lpc2148.h"

void delay(int);

int main() {
    unsigned char a;
    
    PINSEL0 = 0x5;
    U0LCR = 0x83;
    U0DLL = 0x61;
    U0DLM = 0x00;
    U0LCR = 0x03;
    
    while(1) {
        while (!(U0LSR & 0x01)); // Receive condition
        a = U0RBR;
        delay(10);
        while (!(U0LSR & 0x20)); // Transmit condition
        U0THR = a;
    }
}

void delay(int x) {
    unsigned int i, j;
    for (i = 0; i < x; i++)
        for (j = 0; j < 113; j++);
}
