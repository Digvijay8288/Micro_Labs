#include <at89c5131.h>
#include "spi.h"
#include "lcd.h"
#include "mcp3008.h"
#include "serial.h"

char lcd_string[6] = {0, 0, 0, 0, 0, '\0'};
// Function to read full number (multi-digit) from UART
unsigned char read_number_uart() {
    unsigned char ch;
    unsigned int num = 0;

    while (1) {
        ch = receive_char();
        if (ch == '\r' || ch == '\n') break; 
		

        if (ch >= '0' && ch <= '9') {
            transmit_char(ch);  
            num = num * 10 + (ch - '0');
        }
    }
//****************************************************	
//ch - '0' converts ASCII to number:
//'2' (ASCII 50) - '0' (ASCII 48) = 2
//num = num * 10 + digit builds the full number:
//eg. First '2': num = 0 * 10 + 2 = 2
//Then '4': num = 2 * 10 + 4 = 24
//****************************************************

    return (unsigned char)num;  // Return 8-bit result
}

void main(void) {
    unsigned char num1 = 0, num2 = 0;
    unsigned char checkPrime = 0;

    spi_init();     // SPI setup
    lcd_init();     // LCD setup
    uart_init();    // UART setup

    
        lcd_clear();
        lcd_cmd(0x80);
        lcd_write_string("Enter num1:");
				transmit_string("Enter first number:");
        num1 = read_number_uart();
				transmit_string("\r\n");	
				int_to_string(num1, lcd_string);  // Convert sum to string
				lcd_write_string(lcd_string);
        transmit_string("num1: ");
        transmit_string(lcd_string);
        transmit_string("\r\n");	
        lcd_clear();
        lcd_cmd(0x80);
        lcd_write_string("Enter num2:");
				transmit_string("Enter second number:");
        num2 = read_number_uart();
				 transmit_string("\r\n");	
				int_to_string(num2, lcd_string);  // Convert sum to string
				lcd_write_string(lcd_string);
        transmit_string("num2: ");
        transmit_string(lcd_string);
        transmit_string("\r\n");	

        lcd_clear();
        lcd_cmd(0x80);
        lcd_write_string("Sending...");

        spi_trx(num1);
        msdelay(150);
        spi_trx(num2);
        msdelay(150);

        checkPrime = spi_trx(0);  // Get result from slave

        lcd_clear();
        lcd_cmd(0x80);

        if (checkPrime == 1) {
            lcd_write_string("Prime");
            transmit_string("Prime\r\n");
        } else if (checkPrime == 0) {
            lcd_write_string("Not Prime");
            transmit_string("Not Prime\r\n");
        } else {
            lcd_write_string("Error");
            transmit_string("Error\r\n");
        }

        msdelay(1000);  // Delay before next round
				while(1);
    }

