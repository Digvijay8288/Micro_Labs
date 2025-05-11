#include <at89c5131.h>
#include "lcd.h"
#include "spi.h"
#include "serial.h"

char lcd_string[3] = {0};
char lcd_string1[4] = {0};

data unsigned char a1 _at_ 0x70;
data unsigned char a2 _at_ 0x71;
data unsigned char a3 _at_ 0x72;
data unsigned char b1 _at_ 0x73;
data unsigned char b2 _at_ 0x74;
data unsigned char b3 _at_ 0x75;

data unsigned char mac_result _at_ 0x50; // single byte MAC result

extern void MAC_NUMS(void);  // Assembly subroutine

bit check_prime(unsigned int n) {
    unsigned int i;
    if (n < 2) return 0;
    for (i = 2; i * i <= n; i++) {
        if (n % i == 0) return 0;
    }
    return 1;
}

void main(void) {
    unsigned int result;

    spi_init();
    lcd_init();

    lcd_cmd(0x80);
    lcd_write_string("Receiving...");

    // Receive 6 numbers (3 x, 3 y)
    a1 = spi_trx(0);
    a2 = spi_trx(0);
    a3 = spi_trx(0);

    b1 = spi_trx(0);
    b2 = spi_trx(0);
    b3 = spi_trx(0);

    // Call MAC routine
    MAC_NUMS();

    // Read 8-bit result
    result = mac_result;

    // Send 1 if result is prime, else 0
    spi_trx(check_prime(result));

    lcd_clear();
    lcd_cmd(0x80);

    // Display a1 a2 a3
    int_to_string(a1, lcd_string); lcd_write_string(lcd_string);
    lcd_write_string(" "); int_to_string(a2, lcd_string); lcd_write_string(lcd_string);
    lcd_write_string(" "); int_to_string(a3, lcd_string); lcd_write_string(lcd_string);

    lcd_write_string(" ");
    int_to_string(b1, lcd_string); lcd_write_string(lcd_string);
    lcd_cmd(0xC0);
    int_to_string(b2, lcd_string); lcd_write_string(lcd_string);
    lcd_write_string(" "); int_to_string(b3, lcd_string); lcd_write_string(lcd_string);

    // Show MAC result
    lcd_write_string(" MAC:");
    int_to_string(result, lcd_string); lcd_write_string(lcd_string);

    while (1);
}
