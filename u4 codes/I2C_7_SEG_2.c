#include <lpc2148.h>

#define MAX 6
#define AA 2
#define SI 3
#define STO 4
#define STA 5
#define I2EN 6

unsigned char Buff[] = {0x00, 0x27, 0x3F, 0x06, 0x5B, 0x4F};
unsigned char index = 0;

void Delay(void) {
    unsigned int i, j;
    for (i = 0; i < 20; i++)
        for (j = 0; j < 200; j++);
}

void Wait(unsigned int Delay) {
    while (Delay--);
}

void I2C_Init(void) {
    I2C0SCLH = 150; // 50%duty cycle ..... I2C Frequency ->100 KHz for PCLK = 30MHz
    I2C0SCLL = 150;
    I2C0CONSET = 1 << I2EN; // Enable I2C 0
}

int I2C_Start(void) {
    I2C0CONCLR = 1 << STO;
    I2C0CONCLR = 1 << AA;
    I2C0CONSET = 1 << STA;
    return 0;
}

int I2C_Write(unsigned char *Buff, unsigned int Count) {
    while (Count--) {
        I2C0DAT = *Buff++;
    }
    return 0;
}

void main() {
    unsigned int i;
    VPBDIV = 0x02;
    PINSEL0 = 0x00000055; // P0.3 - SDA0 and P0.2 - SCL0
    U0LCR = 0x83;
    U0DLL = 97;
    U0DLM = 0x00;
    U0LCR = 0x03;
    VICIntSelect = 0 << 9;
    VICVectCntl0 = 0x020 | 9;
    VICVectAddr0 = (unsigned long)I2C_ISR;
    VICIntEnable = 1 << 9;
    /* Before the master transmitter mode can be entered, the I2CONSET register must be initialized */
    I2C_Init();
    I2C_Start();
    for (i = 0; i < 30; i++)
        Wait(10000);
    I2C0CONCLR = 1 << SI;
    while (1) {
        for (i = 0; i < 20; i++)
            Wait(10000);
    }
}

void I2C_ISR(void){
    if (I2C0CONSET & 0x08) {
        switch (I2C0STAT) {
            case (0x08):
                I2C0CONCLR = 1 << STA;
                I2C0DAT = 0x70; // Slave Addr + W
                break;
            case (0x10):
                I2C0CONCLR = 1 << STA; // Clear START Bit
                I2C0DAT = 0x70; // This Status is received if "Repeated START" is transmitted
                break;
            case (0x18):
                I2C0CONCLR = 0x20; // Clear START Bit
                I2C0DAT = Buff[index];
                index++;
                break;
            case (0x20):
                I2C0CONCLR = 0x20; // Clear START Bit
                I2C0DAT = Buff[index];
                index++;
                break;
            case (0x28):
                I2C0CONCLR = 0x20; // Clear START Bit
                if (index < MAX) {
                    I2C0DAT = Buff[index];
                    index++;
                } else {
                    index = 0;
                    I2C0CONSET = 0x10; // Send STOP Bit
                }
                break;
            case (0x30):
                I2C0CONCLR = 0x20; // Clear START Bit
                if (index < MAX) {
                    I2C0DAT = Buff[index];
                    index++;
                } else {
                    index = 0;
                    I2C0CONSET = 0x10; // Send STOP Bit
                    I2C_Start();
                }
                break;
            case (0x38):
                I2C0CONSET = 0x20;
                break;
        }
    }
    I2C0CONCLR = 1 << SI;
    VICVectAddr = 0x00;
}
