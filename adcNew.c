#include "lpc2148.h"
#include "stdint.h"
#include "stdio.h"
#include "string.h"

void InitLPC(void)
{
	PINSEL0 = 0x00000000;
    PINSEL1=0x01000000;      
	IO0DIR = 0XFFFFFFFF;
}

void delay_ms(uint16_t j)
{
	uint16_t x,i;
	for(i=0;i<j;i++)
		for(x=0;x<6000;x++);
}

void LCD_Command(char command)
{
	IO0SET = command<<8;
	IO0SET = IO0SET |=0x00000040; /* EN = 1 */

	delay_ms(2);

    IO0CLR = 0x00000040;
    IO0CLR=0xFFFFFFFF;
}


void LCD_Init(void)
{
	LCD_Command(0x38);  /* Initialize lcd */
	LCD_Command(0x0C);   /* Display on cursor off */
	LCD_Command(0x06);  /* Auto increment cursor */
	LCD_Command(0x01);   /* Display clear */
}


void LCD_String (char* msg)
{  
	uint8_t i=0;
    while(msg[i]!=0)
    {
		IO0SET = msg[i]<<8;
		IO0SET = IO0SET |=0x00000050; /* EN = 1 */
		delay_ms(2);
        IO0CLR = 0x00000040;
        delay_ms(5);
        IO0CLR=0xFFFFFFFF;
        i++;
	}
}


int main(void)
{
	uint32_t result;
	float voltage;
	char adc[18];

    InitLPC();
	LCD_Init();
    AD0CR = 0x00200402; /* ADC operational, 10-bits, 11 clocks for conversion */

	while(1)
	{
		AD0CR = AD0CR | (1<<24); /* Start Conversion */

		while ( !(AD0GDR & 0x80000000) ); /* Wait till DONE */
			result = AD0GDR;
		
		result = (result>>6);
		result = (result & 0x000003FF);
        voltage=result;

		LCD_Command(0x80);
		sprintf(adc, "ADC=%f V  ", voltage);
		LCD_String(adc);
	}     
}


// same code with comments 
#include "lpc2148.h"   // Include header file for LPC2148 microcontroller
#include "stdint.h"    // Include standard integer types
#include "stdio.h"     // Include standard I/O library for sprintf function
#include "string.h"    // Include string manipulation functions

void InitLPC(void)
{
    // Initialize the LPC2148 microcontroller
	PINSEL0 = 0x00000000;      // Set all pins in PINSEL0 to GPIO (General Purpose I/O)
    PINSEL1 = 0x01000000;      // Configure P0.25 as DAC output
	IO0DIR = 0xFFFFFFFF;       // Set all pins on port 0 as output
}

void delay_ms(uint16_t j)
{
    // Function to generate a delay in milliseconds
	uint16_t x, i;
	for(i = 0; i < j; i++)
		for(x = 0; x < 6000; x++);  // Inner loop to create the delay
}

void LCD_Command(char command)
{
    // Send a command to the LCD
	IO0SET = command << 8;          // Place the command on the data bus
	IO0SET = IO0SET | 0x00000040;   // Set EN (Enable) pin high to latch the command

	delay_ms(2);                    // Small delay for command to be processed

    IO0CLR = 0x00000040;            // Set EN (Enable) pin low to finish the command cycle
    IO0CLR = 0xFFFFFFFF;            // Clear all outputs on port 0
}

void LCD_Init(void)
{
    // Initialize the LCD display
	LCD_Command(0x38);  // Function set: 8-bit interface, 2 lines, 5x8 dots
	LCD_Command(0x0C);  // Display ON, cursor OFF
	LCD_Command(0x06);  // Entry mode: auto-increment cursor
	LCD_Command(0x01);  // Clear display
}

void LCD_String(char* msg)
{
    // Display a string on the LCD
	uint8_t i = 0;
    while(msg[i] != 0)               // Loop until the end of the string
    {
		IO0SET = msg[i] << 8;        // Place character on the data bus
		IO0SET = IO0SET | 0x00000050; // Set RS (Register Select) and EN (Enable) high

		delay_ms(2);                // Small delay for data to be processed

        IO0CLR = 0x00000040;        // Set EN (Enable) pin low to finish the data cycle
        delay_ms(5);                // Delay before next character
        IO0CLR = 0xFFFFFFFF;        // Clear all outputs on port 0
        i++;
	}
}

int main(void)
{
	uint32_t result;               // Variable to store ADC result
	float voltage;                 // Variable to store calculated voltage
	char adc[18];                  // Buffer to store formatted string

    InitLPC();                     // Initialize the LPC2148 microcontroller
	LCD_Init();                    // Initialize the LCD
    AD0CR = 0x00200402;            // Configure ADC: operational, 10-bits, 11 clocks for conversion

	while(1)
	{
		AD0CR = AD0CR | (1 << 24);  // Start ADC conversion

		while ( !(AD0GDR & 0x80000000) );  // Wait until the conversion is done
		result = AD0GDR;            // Read the ADC result
		
		result = (result >> 6);     // Shift result to get 10-bit value
		result = (result & 0x000003FF); // Mask the lower 10 bits
        voltage = result;          // Assign result to voltage variable

		LCD_Command(0x80);          // Move cursor to the beginning of the first line
		sprintf(adc, "ADC=%f V  ", voltage); // Format the string with the ADC value
		LCD_String(adc);            // Display the string on the LCD
	}     
}
