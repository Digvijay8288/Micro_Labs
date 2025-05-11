#include <at89c5131.h>
#include "spi.h"
#include "lcd.h"
#include "serial.h"

char lcd_string[6] = { 0, '\0'};

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
    return (unsigned char)num;
}

void main(void) {
    unsigned char a1, a2, a3, b1, b2, b3;
    unsigned char checkPrime = 0;

    spi_init();
    lcd_init();
    uart_init();

    // Read a1, a2, a3 via UART
    lcd_clear();
    lcd_cmd(0x80);
    lcd_write_string("Enter X1:");
    transmit_string("Enter X1: ");
    a1 = read_number_uart(); transmit_string("\r\n");

    lcd_clear(); lcd_cmd(0x80);
    lcd_write_string("Enter X2:");
    transmit_string("Enter X2: ");
    a2 = read_number_uart(); transmit_string("\r\n");

    lcd_clear(); lcd_cmd(0x80);
    lcd_write_string("Enter X3:");
    transmit_string("Enter X3: ");
    a3 = read_number_uart(); transmit_string("\r\n");

    // Read b1, b2, b3 via UART
    lcd_clear(); lcd_cmd(0x80);
    lcd_write_string("Enter Y1:");
    transmit_string("Enter Y1: ");
    b1 = read_number_uart(); transmit_string("\r\n");

    lcd_clear(); lcd_cmd(0x80);
    lcd_write_string("Enter Y2:");
    transmit_string("Enter Y2: ");
    b2 = read_number_uart(); transmit_string("\r\n");

    lcd_clear(); lcd_cmd(0x80);
    lcd_write_string("Enter Y3:");
    transmit_string("Enter Y3: ");
    b3 = read_number_uart(); transmit_string("\r\n");

    // Show Sending message
    lcd_clear(); lcd_cmd(0x80);
    lcd_write_string("Sending...");

    // Send 6 values to Slave
    spi_trx(a1); msdelay(100);
    spi_trx(a2); msdelay(100);
    spi_trx(a3); msdelay(100);
    spi_trx(b1); msdelay(100);
    spi_trx(b2); msdelay(100);
    spi_trx(b3); msdelay(100);

    // Receive result from Slave
    checkPrime = spi_trx(0);

    // Show inputs and result
    lcd_clear();
    
    
		lcd_clear();
    lcd_cmd(0x80);
    if (checkPrime == 1) {
        lcd_write_string("Result: Prime");
        transmit_string("MAC Result: Prime\r\n");
    } else {
        lcd_write_string("Result:Not Prime");
        transmit_string("MAC Result: Not Prime\r\n");
    }

    while (1);
}
