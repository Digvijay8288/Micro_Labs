#include <at89c5131.h>
#include "serial.h"
#include "lcd.h"

// Define speaker pin
sbit Speaker = P0^7;
IP = 0xB8;
unsigned char TH_freq;
unsigned char TL_freq;
unsigned char ch;
void timer0_isr() interrupt 1 {
    Speaker = ~Speaker; // Toggle speaker to create square wave
    TH0 = TH_freq;
    TL0 = TL_freq;
    TR0 = 1;
}
// Main function
void main() {
	  IP=0x10;
    uart_init(); // Initialize UART
    lcd_init();  // Initialize LCD
    TMOD = 0x21; 
    ET0 = 1;  // Enable Timer 0 Interrupt
    ES = 1;   // Enable Serial Interrupt
    EA = 1;   // Enable Global Interrupt
	  TR0=0;
	 while (1) {  
  	ch= receive_char();
                switch (ch) {
                case 's': TR0=1;
									        TH_freq=0xEF;
									        TL_freq=0xB9;
									        lcd_cmd(0x80); 
													lcd_write_string("Sa"); 
													transmit_string("Sa\r\n"); break;
                case 'r': TR0=1;
									TH_freq=0xF1;
									TL_freq=0x88;
									lcd_cmd(0x80); 
									lcd_write_string("Re"); 
									transmit_string("Re\r\n"); break;
                case 'g': TR0=1;
									TH_freq=0xF2;
									TL_freq=0xFA;
									lcd_cmd(0x80); 
									lcd_write_string("Ga"); 
									transmit_string("Ga\r\n"); break;
                case 'm': TR0=1;
									TH_freq=0xF3;
									TL_freq=0xCB;
									lcd_cmd(0x80); 
									lcd_write_string("Ma"); 
									transmit_string("Ma\r\n"); break;
                case 'p': TR0=1;
								  TH_freq=0xF5;
									TL_freq=0x26;
									lcd_cmd(0x80); 
									lcd_write_string("Pa"); 
									transmit_string("Pa\r\n"); break;
                case 'd': TR0=1;
								  TH_freq=0xF6;
								  TL_freq=0x3C;
								  lcd_cmd(0x80); 
								  lcd_write_string("Dha"); 
								  transmit_string("Dha\r\n"); break;
                case 'n': TR0=1;
								  TH_freq=0xF7;
									TL_freq=0x51;
								  lcd_cmd(0x80); 
								  lcd_write_string("Ni"); 
								  transmit_string("Ni\r\n"); break;
                case 'a': TR0=1;
								  TH_freq=0xF7;
								  TL_freq=0xDC;
								  lcd_cmd(0x80); 
								  lcd_write_string("Saa"); 
								  transmit_string("Saa\r\n"); break;
                case 'q': 
                    TR0=0;
                    lcd_write_string("Shaanti"); 
                    transmit_string("Shaanti\r\n"); 
                    lcd_cmd(0x01);
                    break;
                default: 
                    lcd_write_string("Invalid Key"); 
                    transmit_string("Invalid Key\r\n"); 
                    break;
            }
								msdelay(100);
        }
    }