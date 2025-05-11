/**********************************************************
EE337: ADC IC MCP3008 interfacing with pt-51
(1) Complete spi_init() function from spi.h 
***********************************************************/

#include <at89c5131.h>
#include "lcd.h"      // Driver for interfacing LCD 
#include "spi.h"      // Driver for interfacing ADC IC MCP3008
#include "serial.h"
char lcd_string[6]={0,0,0,0,0,'\0'};
unsigned int x,y;
bit check_prime(unsigned int n) {
	unsigned int i;
	if (n < 2) return 0;
	for (i = 2; i * i <= n; i++) {
		if (n % i == 0) return 0;
	}
	return 1;
}

void main(void) {
	unsigned int sum;
	
	spi_init();     // Initialize SPI
	lcd_init();     // Initialize LCD

	while (1) {
		lcd_cmd(0x80);                    // Set cursor to beginning
		x=spi_trx(0);
		y=spi_trx(0);
		
		sum = x+y;    // Read two bytes and add

		spi_trx(check_prime(sum));          // Send 1 if prime, else 0
		lcd_write_string("X:");
		int_to_string(x, lcd_string);  // Convert sum to string
		lcd_write_string(lcd_string);
		lcd_write_string("Y:");
		int_to_string(y, lcd_string);  // Convert sum to string
		lcd_write_string(lcd_string);
		lcd_cmd(0xC0);
		int_to_string(sum, lcd_string);  // Convert sum to string
		lcd_write_string(lcd_string);    // Display on LCD			
	}
}
