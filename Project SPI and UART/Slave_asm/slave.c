#include <at89c5131.h>
#include "lcd.h"
#include "spi.h"
#include "serial.h"
char lcd_string[6] = {0, 0, 0, 0, 0, '\0'};

data unsigned char num1 _at_ 0x20;  // Share via internal RAM (starts at 0x20)
data unsigned char num2 _at_ 0x21;
data unsigned char result _at_ 0x22;

extern void ADD_NUMS(void);  // Assembly function

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

    spi_init();
    lcd_init();

   
        lcd_cmd(0x80);
        lcd_write_string("Receiving...");

        num1 = spi_trx(0);
        num2 = spi_trx(0);

        ADD_NUMS();           // Assembly adds num1 + num2 ? result

        sum = result;         // result now holds the sum

        spi_trx(check_prime(sum));   // send prime result to master
				lcd_clear();
        lcd_write_string("X:");
				int_to_string(num1, lcd_string);  // Convert sum to string
				lcd_write_string(lcd_string);
				
				lcd_write_string(" Y:");
				int_to_string(num2, lcd_string);  // Convert sum to string
				lcd_write_string(lcd_string);
				
				lcd_cmd(0xC0);
				lcd_write_string("ASM_Sum:");
				int_to_string(result, lcd_string);  // Convert sum to string
				lcd_write_string(lcd_string);
			 while (1) ;		
    
}
