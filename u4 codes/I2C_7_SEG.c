#include "lpc2148.h" 
#include <stdint.h> 

void delay(unsigned int c) { 
    unsigned int a; 
    for(a=1; a<=6000; a++); 
} 

#define I2EN (1<<6) // Enable/Disable bit 
#define STA (1<<5)  // Start Set/Clear bit 
#define STO (1<<4)  // Stop bit 
#define SI (1<<3)   // Serial Interrupt Flag Clear bit 
#define AA (1<<2)   // Assert Acknowledge Set/Clear bit 

void waitforsi(void) { 
    while (!(I2C0CONSET & SI)); // Wait till SI goes 1 
} 

void i2c_send_start(void) { 
    I2C0CONSET = STA; // Set start bit
    waitforsi(); // Wait for interrupt to set
} 

void i2c_write(unsigned char data) { 
    I2C0DAT = data; // Load data 
    I2C0CONCLR = SI | STA | AA; // Clear interrupt, start, ack 
    waitforsi(); // Wait for condition to transmit 
} 

void i2c_send_stop(void) { 
    I2C0CONCLR = AA | SI; // Clear ack and interrupt 
    I2C0CONSET = STO; // Send stop 
} 

void i2c_init(void) { 
    I2C0SCLH = 75; // 15MHz/150 = 100000 speed i2c 
    I2C0SCLL = 75; 
    I2C0CONCLR = STA | STO | AA | SI; // Clear all bits 
    I2C0CONSET = I2EN; // Enable bit set 
} 

void lcd_write_data(int data) { 
    unsigned char address = 0x4C;
    unsigned char a[] = {0x3f, 0x6, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x7, 0x7f, 0x6f}; 
    i2c_send_start(); 
    i2c_write(address); 
    i2c_write(a[data]); 
    i2c_send_stop(); 
} 

int main() { 
    int l; 
    PINSEL0 = (1<<4) | (1<<6); // For i2c line 
    i2c_init(); 
    while(1) { 
        for(l=0; l<10; l++) { 
            lcd_write_data(l); 
            delay(2); 
        } 
    } 
}
