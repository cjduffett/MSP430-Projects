#include <msp430g2553.h>
/* EC450 Homework 03
 * Echo Light
 * ----------------------
 * Carlton Duffett
 * 2-21-2015
 *
 * This program records a series of button presses on the MSP430 launchpad button
 * (P1.3) that flash the on-board green LED. After recording, the series of flashes
 * is played back to the user. Once playback is finished, the program returns to
 * record mode to record another message.
 *
 * To control this behavior the program has the following modes:
 *
 * RECORD mode = 'r':
 * ------------------
 * Recording is indicated by a steady red light. Button presses are recorded until:
 * 1. The available memory is used up. This happens after 100 button presses.
 * 2. The available recording time is used up. This happens after ~ 2 minutes.
 * 3. The user does not press the button for more than 4 seconds.
 *
 * Transition to playback mode is indicated by 3 red flashes with the red LED finishing
 * in the off position.
 *
 * PLAYBACK mode = 'p':
 * --------------------
 * Playback occurs when the red LED is off. Playback of a recorded sequence runs until:
 * 1. The end of the recording is reached.
 * 2. The available playback time is used up. This happens after ~ 2 minutes.
 *
 * Transition TO = 't' / FROM = 'f' playback mode:
 * -----------------------------------------------
 * Transitions are indicated by 3 red flashes. Transitions occur when any of the
 * conditions described above (for recording or playback) are met.
 *
 * main.c
 */

// I/O pin mappings
#define RED_LED 	0x01
#define GREEN_LED 	0x60
#define BUTTON 		0x08

// Constants
#define MEM_SIZE 	200		// Maximum size of the memory array (100 button presses)
#define MAX_TIME	16000 	// Maximum number of intervals to record for (~ 2 mins)
#define WAIT_TIME	500		// Maximum time to wait for user action before going to Playback (~ 4 sec)
#define BLINK_TIME	30		// Time between blinks during transition mode (~ .3 sec)

// Global variables
volatile unsigned int i_counter;	// Counts the number of interrupts since record/playback start
volatile unsigned int t_counter;	// Counts the number of button transitions (ON/OFF)
volatile unsigned int t[MEM_SIZE]; 	// Array containing ints monitoring when the button is pressed
volatile unsigned char last_button;	// The button state at the last interrupt
volatile char mode;					// Current operation mode ('r','p','t', or 'f')

// Functions
void resetTransitionArray(void);
void setupTransition(char);
void transition(char);
void record(void);
void playback(void);

int main(void)
{
	// setup the watchdog timer as an interval timer
	WDTCTL =(WDTPW +  WDTTMSEL + WDTCNTCL +  0  + 1);

	// enable the WDT interrupt (in the system interrupt register IE1)
	IE1 |= WDTIE;

	P1DIR |= RED_LED + GREEN_LED;	// Red and Green LEDs are outputs
	P1DIR &= ~BUTTON;				// Button is an input

	P1OUT &= ~GREEN_LED;			// Green LED off
	P1OUT |= RED_LED;				// Red LED on for initial record mode

	P1OUT |= BUTTON;				// Connect button internally to Vcc
	P1REN |= BUTTON;				// Enable pull-up resistor


	//Initialize global variables
	i_counter = 0;
	t_counter = 0;
	last_button = BUTTON; // not pressed
	mode = 'r';
	resetTransitionArray();

	_bis_SR_register(GIE+LPM0_bits);  // enable interrupts and turn CPU off

	return 0;
}

// Watchdog Timer interrupt handler
// Called every 7.4ms
interrupt void WDT_interval_handler() {

	switch (mode) {

	case 'r':
		record();
		break;

	case 'p':
		playback();
		break;

	case 't':
		transition('p');
		break;

	case 'f':
		transition('r');
		break;

	} // end switch
} // end interrupt handler


// Clear the transition array and set all entries to 0
void resetTransitionArray(void) {
	int i;
	for (i = 0; i < MEM_SIZE; i++){
		t[i] = 0; // reset all contents to 0
	}
}

// Setup global variables for each transition
void setupTransition(char nextMode) {
	// clear counters
	i_counter = 0;
	t_counter = 0;

	// turn off LEDs
	P1OUT &= ~(RED_LED + GREEN_LED);

	// set next mode
	mode = nextMode;
}

// Indicate transition using RED LED blinks
void transition(char nextMode) {

	if (t_counter > 5) {
		// transition to next mode
		setupTransition(nextMode);

		if (nextMode == 'r') {
			P1OUT |= RED_LED; // indicate record mode
			resetTransitionArray();
		}

		if (nextMode == 'p') {
			// adjust start of playback to first recorded button press
			if (t[0] > WAIT_TIME) {
				i_counter = t[0] - 100;
			}
		}
	}
	else {
		// blink RED LED to indicate transition
		if (i_counter == BLINK_TIME) {
			i_counter = 0;
			P1OUT ^= RED_LED;
			t_counter += 1;
		}
		i_counter += 1;
	}
} // end transition

// Record button presses and transition when limit(s) are reached
void record(void) {

	char this_button = (P1IN & BUTTON);

	// memory limit reached
	if (t_counter == MEM_SIZE) {
		setupTransition('t');
	}

	// recording time limit reached
	else if (i_counter == MAX_TIME) {

		// button depressed during timeout
		if (!this_button) {
			// record last transition as button release
			t[t_counter] = i_counter;
		}
		setupTransition('t');
	}

	// user waits more than 4 seconds since last button press
	else if (last_button && (i_counter - t[t_counter - 1]) > WAIT_TIME && t_counter > 0) {
		setupTransition('t');
	}

	// continue recording
	else {
		i_counter += 1;

		if (this_button != last_button) {
			t[t_counter] = i_counter;
			t_counter += 1;
		}
	}

	// toggle GREEN LED:
	if (!this_button) {
		P1OUT |= GREEN_LED;
	}
	else {
		P1OUT &= ~GREEN_LED;
	}

	last_button = this_button;
} // end record


// Playback button presses until limit(s) are reached
 void playback(void) {

	// memory limit reached
	if (t_counter == MEM_SIZE) {
		setupTransition('f');
	}

	// reached end of recording
	else if (t[t_counter] == 0 && t_counter > 0) {
		setupTransition('f');
	}

	// playback timed out
	else if (i_counter == MAX_TIME) {
		setupTransition('f');
	}

	// continue playback
	else {
		i_counter += 1;
		if (i_counter == t[t_counter]) {
			P1OUT ^= GREEN_LED;
			t_counter += 1;
		}
	}
} // end playback

// DECLARE function WDT_interval_handler as handler for interrupt 10
// using a macro defined in the msp430g2553.h include file
ISR_VECTOR(WDT_interval_handler, ".int10")
