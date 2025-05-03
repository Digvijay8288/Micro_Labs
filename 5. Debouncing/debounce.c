#include <at89c5131.h>  // Header for AT89C5131 microcontroller

// Switches as input pins
sbit SW1 = P1^0;
sbit SW2 = P1^1;
sbit SW3 = P1^2;
sbit SW4 = P1^3;

// LEDs as output pins
sbit LED1 = P1^4;
sbit LED2 = P1^5;
sbit LED3 = P1^6;
sbit LED4 = P1^7;

// Delay function in milliseconds
void msdelay(unsigned int time) {
    unsigned int i, j;
    for (i = 0; i < time; i++) {
        for (j = 0; j < 382; j++);
    }
}

// Function to turn OFF all LEDs
void turnOffAllLEDs() {
    LED1 = 0;
    LED2 = 0;
    LED3 = 0;
    LED4 = 0;
}

// Function to turn ON all LEDs for 1 second
void flashAllLEDs() {
    LED1 = 1;
    LED2 = 1;
    LED3 = 1;
    LED4 = 1;
    msdelay(1000);  // 1-second delay
    turnOffAllLEDs();
}

// Global variables to track switch states
unsigned char prevState = 0x0F;  // Initial state: All switches OFF (pull-up active)
unsigned char currState;

void main() {
    // Configure P1.0 to P1.3 as inputs and P1.4 to P1.7 as outputs
    P1 = 0x0F;  // Set P1.0–P1.3 as inputs, P1.4–P1.7 as outputs

    while (1) {
        currState = P1 & 0x0F;  // Read the state of SW1 to SW4

        // Check for state change
        if (currState != prevState) {
            msdelay(2000);  // 2-second debounce delay

            // Read the state again after debounce delay
            if ((P1 & 0x0F) == currState) {  // Confirm stable state
                if (currState != prevState) {
                    // OFF-to-ON transitions (active LOW)
                    if ((prevState & 0x01) && !(currState & 0x01)) {
                        turnOffAllLEDs();
                        LED1 = 1;
                    } 
                    else if ((prevState & 0x02) && !(currState & 0x02)) {
                        turnOffAllLEDs();
                        LED2 = 1;
                    } 
                    else if ((prevState & 0x04) && !(currState & 0x04)) {
                        turnOffAllLEDs();
                        LED3 = 1;
                    } 
                    else if ((prevState & 0x08) && !(currState & 0x08)) {
                        turnOffAllLEDs();
                        LED4 = 1;
                    }

                    // ON-to-OFF transitions
                    if (!(prevState & 0x01) && (currState & 0x01)) {
                        flashAllLEDs();
                    } 
                    else if (!(prevState & 0x02) && (currState & 0x02)) {
                        flashAllLEDs();
                    } 
                    else if (!(prevState & 0x04) && (currState & 0x04)) {
                        flashAllLEDs();
                    } 
                    else if (!(prevState & 0x08) && (currState & 0x08)) {
                        flashAllLEDs();
                    }

                    // Update previous state
                    prevState = currState;
                }
            }
        }
    }
}