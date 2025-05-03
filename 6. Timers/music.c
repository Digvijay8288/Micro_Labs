#include <AT89C5131.h>  // Standard 8051 header file

sbit SPEAKER = P0^7;  // Speaker connected to P0.7

// Function Prototypes
void play_note(unsigned int reload_value, unsigned int duration);
void delay_ms(unsigned int duration);

// Musical Note Frequencies - Timer 0 Reload Values for 12MHz 8051
#define NOTE_SA_LOW  0xEFB9  // 240 Hz
#define NOTE_RE      0xF188  // 270 Hz
#define NOTE_GA      0xF2FB  // 300 Hz
#define NOTE_MA      0xF3CB  // 320 Hz
#define NOTE_PA      0xF526  // 360 Hz
#define NOTE_DHA     0xF63C  // 400 Hz
#define NOTE_NI      0xF752  // 450 Hz
#define NOTE_SA_HIGH 0xF7DD  // 480 Hz

// Notes duration in milliseconds
unsigned int durations[] = {500, 750, 1000, 500, 1000, 750, 1000, 500};  // Total: 6 seconds

// Notes frequency values
unsigned int notes[] = {
    NOTE_SA_LOW, NOTE_RE, NOTE_GA, NOTE_MA,
    NOTE_PA, NOTE_DHA, NOTE_NI, NOTE_SA_HIGH
};

// Global variable to hold the current note reload value
unsigned int current_note;

// Timer 0 ISR - Toggles Speaker Pin to Generate Square Wave
void timer0_isr(void) interrupt 1 {
    SPEAKER = ~SPEAKER;  // Toggle speaker
    TH0 = current_note >> 8;   // Reload high byte
    TL0 = current_note & 0xFF; // Reload low byte
    TF0 = 0;  // *Clear Timer 0 Overflow Flag*
}

// Main Function
void main() {
    int i;

    TMOD = 0x11;  // Timer 0 and Timer 1 in Mode 1 (16-bit mode)
    
    EA = 1;   // Enable global interrupts
    ET0 = 1;  // Enable Timer 0 interrupts

    for (i = 0; i < 8; i++) {
        play_note(notes[i], durations[i]);  // Play each note
    }

    while (1);  // Infinite loop after playing notes
}

// Function to play a note for a given duration
void play_note(unsigned int reload_value, unsigned int duration) {
    current_note = reload_value; // Store reload value for ISR

    TH0 = reload_value >> 8;   // Load high byte
    TL0 = reload_value & 0xFF; // Load low byte
    TR0 = 1;  // Start Timer 0

    delay_ms(duration);  // Play for given duration

    TR0 = 0;  // Stop Timer 0
    TF0 = 0;  // *Ensure Timer 0 Flag is Cleared*
    SPEAKER = 0;  // Ensure speaker is OFF after the note
}

// Function to generate a precise delayusing Timer 1
void delay_ms(unsigned int duration) {
    while (duration > 0) {
        TH1 = 0xF8;  // Load for *exact* 1ms delay
        TL1 = 0x30;  // Adjusted to maintain precise timing
        TR1 = 1;
        while (TF1 == 0){};  // Wait for Timer1 overflow
        TR1 = 0;
        TF1 = 0;
        duration--;  // Decrease duration *precisely*
    }
}