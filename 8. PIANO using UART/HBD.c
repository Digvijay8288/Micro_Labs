#include <at89c5131.h>
#include "lcd.h"
#include "serial.h"

sbit buzzer = P1^0;  // Buzzer connected to Port 1.0

// Frequency values for each note (Timer 1 reload values)
#define Sa  0xEFB9  // Adjust based on calculations
#define Re  0xF188
#define Ga  0xF2FB
#define Ma  0xF3CB
#define Pa  0xF526
#define Dha 0xF63C
#define Ni  0xF752
#define SaH 0xF7DD  // Higher Sa

void delay(unsigned int time);
void play_note(unsigned char note);

void timer_ISR(void) interrupt 3  // Timer interrupt
{
    buzzer = ~buzzer; // Toggle buzzer pin
}

void play_song()
{
    unsigned char notes[] = {Sa, Sa, Re, Sa, Ma, Ga, Sa, Sa, Re, Sa, Pa, Ma, Sa, Sa, SaH, Dha, Ma, Ga, Re, Dha, Dha, Dha, Ma, Pa, Ma};
    unsigned int i;
    
    for (i = 0; i < sizeof(notes); i++)
    {
        play_note(notes[i]);  // Play each note
        delay(500);           // Delay between notes
    }
}

void play_note(unsigned char note)
{
    TH1 = note;    // Set timer frequency
    TR1 = 1;       // Start Timer
    delay(500);    // Play for some time
    TR1 = 0;       // Stop Timer
}

void delay(unsigned int time)
{
    unsigned int i, j;
    for(i=0; i<time; i++)
        for(j=0; j<1275; j++);
}

void main()
{
    char received;  
	  lcd_init();
    uart_init();
    received = receive_char();
    // Timer 1 Mode 2
    TMOD = 0x20;  
    TH1 = Sa;  // Default note
    TR1 = 1;
    
    ET1 = 1;  // Enable Timer 1 interrupt
    EA = 1;   // Enable global interrupt
    transmit_string("Happy Birthday To You");
    lcd_write_string("Playing Music...");
    play_song();
    
    while(1);
}
