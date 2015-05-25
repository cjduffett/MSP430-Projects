#include <msp430g2553.h>

// MUSIC BOX
// Carlton Duffett
// 3/22/2015


// define the P1 port bitmask
//----------------------------------
#define LED             0x01
#define SPEAKER         0x02    // TA0 is on this pin
#define RESET_BUTTON    0x04
#define PLAY_BUTTON     0x08
#define SLOW_BUTTON     0x10
#define FAST_BUTTON     0x20
#define SONG1_BUTTON    0X40
#define SONG2_BUTTON    0x80

// define the note frequencies by half-period
// Two octaves from C5 to C7
//-------------------------------------------
#define NUM_NOTES   26

#define _R      1 // inaudible frequency

#define _C4     1911
#define _C4s    1803 // sharp
#define _D4     1703
#define _E4b    1607 // flat
#define _E4     1517
#define _F4     1432
#define _F4s    1351 // sharp
#define _G4     1276
#define _G4s    1204 // sharp
#define _A4     1136
#define _B4b    1073 // flat
#define _B4     1012
#define _C5     956
#define _C5s    902 // sharp
#define _D5     851
#define _E5b    803 // flat
#define _E5     758
#define _F5     716
#define _F5s    676 // sharp
#define _G5     638
#define _G5s    602 // sharp
#define _A5     568
#define _B5b    536 // flat
#define _B5     506
#define _C6     478
/*
#define _C6s    451 // sharp
#define _D6     426
#define _E6b    401 // flat
#define _E6     379
#define _F6     358
#define _F6s    338 // sharp
#define _G6     319
#define _G6s    301 // sharp
#define _A6     285
#define _B6b    268 // flat
#define _B6     253
#define _C7     239
*/
const unsigned int notes[NUM_NOTES] = {
        _R, // rest (inaudible frequency)
        _C4,_C4s,_D4,_E4b,_E4,_F4,_F4s,_G4,_G4s,_A4,_B4b,_B4, // 5th octave
        _C5,_C5s,_D5,_E5b,_E5,_F5,_F5s,_G5,_G5s,_A5,_B5b,_B5, // 6th octave
        _C6
};

// bit mask for defining the score
#define R       0x00
#define C4      0x01
#define C4s     0x02
#define D4      0x03
#define E4b     0x04
#define E4      0x05
#define F4      0x06
#define F4s     0x07
#define G4      0x08
#define G4s     0x09
#define A4      0x0A
#define B4b     0x0B
#define B4      0x0C
#define C5      0x0D
#define C5s     0x0E
#define D5      0x0F
#define E5b     0x10
#define E5      0x11
#define F5      0x12
#define F5s     0x13
#define G5      0x14
#define G5s     0x15
#define A5      0x16
#define B5b     0x17
#define B5      0x18
#define C6      0x19

#define NOTE_MASK   0x1F    // bit mask for isolating notes in score

// define note durations
//----------------------------------
#define NUM_DURATIONS   8

const unsigned char durations[NUM_DURATIONS] = {
        1,  // quick break between adjacent notes of the same frequency
        8,  // sixteenth note duration
        16, // eigth
        24, // dotted eigth
        32, // quarter
        48, // dotted quarter
        64, // half
        96  // dotted half
};

// bit mask for defining the score
#define BREAK       0x00    // break between adjacent notes
#define SIXTEENTH   0x20
#define EIGTH       0x40
#define D_EIGTH     0x60    // dotted eigth
#define QUARTER     0x80
#define D_QUARTER   0xA0    // dotted quarter
#define HALF        0xC0
#define D_HALF      0xE0    // dotted half

// To save space there is no whole note representation. This is simply
// replaced by two half notes of the same frequency.

// define "Joy to the World"
//----------------------------------
#define SONG1_LENGTH    72

unsigned const char song1[SONG1_LENGTH] = {
    (QUARTER + C5),     // 1st measure
    (D_EIGTH + B4),
    (SIXTEENTH + A4),
    (D_QUARTER + G4),   // 2nd measure
    (EIGTH + F4),
    (QUARTER + E4),     // 3
    (QUARTER + D4),
    (D_QUARTER + C4),   // 4
    (EIGTH + G4),
    (D_QUARTER + A4),   // 5
    (BREAK + R),
    (EIGTH + A4),
    (D_QUARTER + B4),   // 6
    (BREAK + R),
    (EIGTH + B4),
    (D_QUARTER + C5),   // 7
    (BREAK + R),
    (EIGTH + C5),
    (BREAK + R),
    (EIGTH + C5),       // 8
    (EIGTH + B4),
    (EIGTH + A4),
    (EIGTH + G4),
    (BREAK + R),
    (D_EIGTH + G4),     // 9
    (SIXTEENTH + F4),
    (EIGTH + E4),
    (EIGTH + C5),
    (BREAK + R),
    (EIGTH + C5),       // 10
    (EIGTH + B4),
    (EIGTH + A4),
    (EIGTH + G4),
    (BREAK + R),
    (D_EIGTH + G4),     // 11
    (SIXTEENTH + F4),
    (EIGTH + E4),
    (BREAK + R),
    (EIGTH + E4),
    (BREAK + R),
    (EIGTH + E4),       // 12
    (BREAK + R),
    (EIGTH + E4),
    (BREAK + R),
    (EIGTH + E4),
    (BREAK + R),
    (SIXTEENTH + E4),
    (SIXTEENTH + F4),
    (D_QUARTER + G4),   // 13
    (SIXTEENTH + F4),
    (SIXTEENTH + E4),
    (EIGTH + D4),       // 14
    (BREAK + R),
    (EIGTH + D4),
    (BREAK + R),
    (EIGTH + D4),
    (BREAK + R),
    (SIXTEENTH + D4),
    (SIXTEENTH + E4),
    (D_QUARTER + F4),   // 15
    (SIXTEENTH + E4),
    (SIXTEENTH + D4),
    (EIGTH + E4),       // 16
    (QUARTER + C5),
    (EIGTH + A4),
    (D_EIGTH + G4),     // 17
    (SIXTEENTH + F4),
    (EIGTH + E4),
    (EIGTH + F4),
    (QUARTER + E4),     // 18
    (QUARTER + D4),
    (HALF + C4)         // 19
};

// define "Super Mario Theme"
//----------------------------------
#define SONG2_LENGTH    418

unsigned const char song2[SONG2_LENGTH] = {
    (SIXTEENTH + E5),   // measure 1
    (BREAK + R),
    (SIXTEENTH + E5),
    (SIXTEENTH + R),    // 16th rest
    (SIXTEENTH + E5),
    (SIXTEENTH + R),    // 16th rest
    (SIXTEENTH + C5),
    (EIGTH + E5),
    (EIGTH + G5),       // measure 2
    (EIGTH + R),        // 8th rest
    (EIGTH + G4),
    (EIGTH + R),
    (D_EIGTH + C5),     // 3
    (SIXTEENTH + G4),
    (EIGTH + R),
    (EIGTH + E4),
    (SIXTEENTH + E4),   // 4
    (EIGTH + A4),
    (EIGTH + B4),
    (SIXTEENTH + B4b),
    (EIGTH + A4),
    (SIXTEENTH + G4),   // 5
    (EIGTH + E5),       // triplet
    (SIXTEENTH + G5),
    (EIGTH + A5),
    (SIXTEENTH + F5),
    (SIXTEENTH + G5),
    (SIXTEENTH + R),    // 6
    (EIGTH + E5),
    (SIXTEENTH + C5),
    (SIXTEENTH + D5),
    (EIGTH + B4),
    (SIXTEENTH + R),
    (D_EIGTH + C5),     // 7
    (SIXTEENTH + G4),
    (EIGTH + R),
    (EIGTH + E4),
    (SIXTEENTH + E4),   // 8
    (EIGTH + A4),
    (EIGTH + B4),
    (SIXTEENTH + B4b),
    (EIGTH + A4),
    (SIXTEENTH + G4),   // 9
    (EIGTH + E5),       // triplet
    (SIXTEENTH + G5),
    (EIGTH + A5),
    (SIXTEENTH + F5),
    (SIXTEENTH + G5),
    (SIXTEENTH + R),    // 10
    (EIGTH + E5),
    (SIXTEENTH + C5),
    (SIXTEENTH + D5),
    (EIGTH + B4),
    (SIXTEENTH + R),
    (EIGTH + R),        // 11
    (SIXTEENTH + G5),
    (SIXTEENTH + F5s),
    (SIXTEENTH + F5),
    (EIGTH + E5b),
    (SIXTEENTH + E5),
    (SIXTEENTH + R),    // 12
    (SIXTEENTH + G4s),
    (SIXTEENTH + A4),
    (SIXTEENTH + C5),
    (SIXTEENTH + R),
    (SIXTEENTH + A4),
    (SIXTEENTH + C5),
    (SIXTEENTH + D5),
    (EIGTH + R),        // 13
    (SIXTEENTH + G5),
    (SIXTEENTH + F5s),
    (SIXTEENTH + F5),
    (EIGTH + E5b),
    (SIXTEENTH + E5),
    (SIXTEENTH + R),    // 14
    (SIXTEENTH + C6),
    (SIXTEENTH + R),
    (SIXTEENTH + C6),
    (BREAK + R),
    (QUARTER + C6),
    (EIGTH + R),        // 15
    (SIXTEENTH + G5),
    (SIXTEENTH + F5s),
    (SIXTEENTH + F5),
    (EIGTH + E5b),
    (SIXTEENTH + E5),
    (SIXTEENTH + R),    // 16
    (SIXTEENTH + G4s),
    (SIXTEENTH + A4),
    (SIXTEENTH + C5),
    (SIXTEENTH + R),
    (SIXTEENTH + A4),
    (SIXTEENTH + C5),
    (SIXTEENTH + D5),
    (EIGTH + R),        // 17
    (EIGTH + E5b),
    (SIXTEENTH + R),
    (EIGTH + D5),
    (SIXTEENTH + R),
    (QUARTER + C5),     // 18
    (QUARTER + R),      // quarter rest
    // REPEAT 11 - 18
    (EIGTH + R),        // 11
    (SIXTEENTH + G5),
    (SIXTEENTH + F5s),
    (SIXTEENTH + F5),
    (EIGTH + E5b),
    (SIXTEENTH + E5),
    (SIXTEENTH + R),    // 12
    (SIXTEENTH + G4s),
    (SIXTEENTH + A4),
    (SIXTEENTH + C5),
    (SIXTEENTH + R),
    (SIXTEENTH + A4),
    (SIXTEENTH + C5),
    (SIXTEENTH + D5),
    (EIGTH + R),        // 13
    (SIXTEENTH + G5),
    (SIXTEENTH + F5s),
    (SIXTEENTH + F5),
    (EIGTH + E5b),
    (SIXTEENTH + E5),
    (SIXTEENTH + R),    // 14
    (SIXTEENTH + C6),
    (SIXTEENTH + R),
    (SIXTEENTH + C6),
    (BREAK + R),
    (QUARTER + C6),
    (EIGTH + R),        // 15
    (SIXTEENTH + G5),
    (SIXTEENTH + F5s),
    (SIXTEENTH + F5),
    (EIGTH + E5b),
    (SIXTEENTH + E5),
    (SIXTEENTH + R),    // 16
    (SIXTEENTH + G4s),
    (SIXTEENTH + A4),
    (SIXTEENTH + C5),
    (SIXTEENTH + R),
    (SIXTEENTH + A4),
    (SIXTEENTH + C5),
    (SIXTEENTH + D5),
    (EIGTH + R),        // 17
    (EIGTH + E5b),
    (SIXTEENTH + R),
    (EIGTH + D5),
    (SIXTEENTH + R),
    (QUARTER + C5),     // 18
    (QUARTER + R),      // quarter rest
    // END REPEAT
    (SIXTEENTH + C5),   // 19
    (BREAK + R),
    (EIGTH + C5),
    (BREAK + R),
    (SIXTEENTH + C5),
    (SIXTEENTH + R),
    (SIXTEENTH + C5),
    (EIGTH + D5),
    (SIXTEENTH + E5),   // 20
    (EIGTH + C5),
    (SIXTEENTH + A4),
    (QUARTER + G4),
    (SIXTEENTH + C5),   // 21
    (BREAK + R),
    (EIGTH + C5),
    (BREAK + R),
    (SIXTEENTH + C5),
    (SIXTEENTH + R),
    (SIXTEENTH + C5),
    (SIXTEENTH + D5),
    (SIXTEENTH + E5),
    (HALF + R),         // 22
    (SIXTEENTH + C5),   // 23
    (BREAK + R),
    (EIGTH + C5),
    (BREAK + R),
    (SIXTEENTH + C5),
    (SIXTEENTH + R),
    (SIXTEENTH + C5),
    (EIGTH + D5),
    (SIXTEENTH + E5),   // 24
    (EIGTH + C5),
    (SIXTEENTH + A4),
    (QUARTER + G4),
    (SIXTEENTH + E5),   // 25
    (BREAK + R),
    (SIXTEENTH + E5),
    (SIXTEENTH + R),
    (SIXTEENTH + E5),
    (SIXTEENTH + R),
    (SIXTEENTH + C5),
    (EIGTH + E5),
    (EIGTH + G5),       // 26
    (EIGTH + R),
    (EIGTH + G4),
    (EIGTH + R),
    (D_EIGTH + C5),     // 27
    (SIXTEENTH + G4),
    (EIGTH + R),
    (EIGTH + E4),
    (SIXTEENTH + E4),   // 28
    (EIGTH + A4),
    (EIGTH + B4),
    (SIXTEENTH + B4b),
    (EIGTH + A4),
    (SIXTEENTH + G4),   // 29
    (EIGTH + E5),       // triplet
    (SIXTEENTH + G5),
    (EIGTH + A5),
    (SIXTEENTH + F5),
    (SIXTEENTH + G5),
    (SIXTEENTH + R),    // 30
    (EIGTH + E5),
    (SIXTEENTH + C5),
    (SIXTEENTH + D5),
    (EIGTH + B4),
    (SIXTEENTH + R),
    (D_EIGTH + C5),     // 31
    (SIXTEENTH + G4),
    (EIGTH + R),
    (EIGTH + E4),
    (SIXTEENTH + E4),   // 32
    (EIGTH + A4),
    (EIGTH + B4),
    (SIXTEENTH + B4b),
    (EIGTH + A4),
    (SIXTEENTH + G4),   // 33
    (EIGTH + E5),       // triplet
    (SIXTEENTH + G5),
    (EIGTH + A5),
    (SIXTEENTH + F5),
    (SIXTEENTH + G5),
    (SIXTEENTH + R),    // 34
    (EIGTH + E5),
    (SIXTEENTH + C5),
    (SIXTEENTH + D5),
    (EIGTH + B4),
    (SIXTEENTH + R),
    (SIXTEENTH + E5),   // 35
    (EIGTH + C5),
    (SIXTEENTH + G4),
    (EIGTH + R),
    (EIGTH + G4s),
    (SIXTEENTH + A4),   // 36
    (EIGTH + F5),
    (BREAK + R),
    (SIXTEENTH + F5),
    (QUARTER + A4),
    (SIXTEENTH + B4),   // 37
    (EIGTH + A5),
    (BREAK + R),
    (SIXTEENTH + A5),
    (BREAK + R),
    (SIXTEENTH + A5),
    (EIGTH + G5),
    (SIXTEENTH + F5),
    (SIXTEENTH + E5),   // 38
    (EIGTH + C5),
    (SIXTEENTH + A4),
    (QUARTER + G4),
    (SIXTEENTH + E5),   // 39
    (EIGTH + C5),
    (SIXTEENTH + G4),
    (EIGTH + R),
    (EIGTH + G4s),
    (SIXTEENTH + A4),   // 40
    (EIGTH + F5),
    (BREAK + R),
    (SIXTEENTH + F5),
    (QUARTER + A4),
    (SIXTEENTH + B4),   // 41
    (EIGTH + F5),
    (BREAK + R),
    (SIXTEENTH + F5),
    (BREAK + R),
    (SIXTEENTH + F5),
    (EIGTH + E5),
    (SIXTEENTH + D5),
    (QUARTER + C5),     // 42
    (QUARTER + C4),
    // REPEAT 35-42
    (SIXTEENTH + E5),   // 35
    (EIGTH + C5),
    (SIXTEENTH + G4),
    (EIGTH + R),
    (EIGTH + G4s),
    (SIXTEENTH + A4),   // 36
    (EIGTH + F5),
    (BREAK + R),
    (SIXTEENTH + F5),
    (QUARTER + A4),
    (SIXTEENTH + B4),   // 37
    (EIGTH + A5),
    (BREAK + R),
    (SIXTEENTH + A5),
    (BREAK + R),
    (SIXTEENTH + A5),
    (EIGTH + G5),
    (SIXTEENTH + F5),
    (SIXTEENTH + E5),   // 38
    (EIGTH + C5),
    (SIXTEENTH + A4),
    (QUARTER + G4),
    (SIXTEENTH + E5),   // 39
    (EIGTH + C5),
    (SIXTEENTH + G4),
    (EIGTH + R),
    (EIGTH + G4s),
    (SIXTEENTH + A4),   // 40
    (EIGTH + F5),
    (BREAK + R),
    (SIXTEENTH + F5),
    (QUARTER + A4),
    (SIXTEENTH + B4),   // 41
    (EIGTH + F5),
    (BREAK + R),
    (SIXTEENTH + F5),
    (BREAK + R),
    (SIXTEENTH + F5),
    (EIGTH + E5),
    (SIXTEENTH + D5),
    (QUARTER + C5),     // 42
    (QUARTER + C4),
    // END REPEAT
    (SIXTEENTH + C5),   // 43
    (BREAK + R),
    (EIGTH + C5),
    (BREAK + R),
    (SIXTEENTH + C5),
    (SIXTEENTH + R),
    (SIXTEENTH + C5),
    (EIGTH + D5),
    (SIXTEENTH + E5),   // 44
    (EIGTH + C5),
    (SIXTEENTH + A4),
    (QUARTER + G4),
    (SIXTEENTH + C5),   // 45
    (BREAK + R),
    (EIGTH + C5),
    (BREAK + R),
    (SIXTEENTH + C5),
    (SIXTEENTH + R),
    (SIXTEENTH + C5),
    (SIXTEENTH + D5),
    (SIXTEENTH + E5),
    (HALF + R),         // 46
    (SIXTEENTH + C5),   // 47
    (BREAK + R),
    (EIGTH + C5),
    (BREAK + R),
    (SIXTEENTH + C5),
    (SIXTEENTH + R),
    (SIXTEENTH + C5),
    (EIGTH + D5),
    (SIXTEENTH + E5),   // 48
    (EIGTH + C5),
    (SIXTEENTH + A4),
    (QUARTER + G4),
    (SIXTEENTH + E5),   // 49
    (BREAK + R),
    (SIXTEENTH + E5),
    (SIXTEENTH + R),
    (SIXTEENTH + E5),
    (SIXTEENTH + R),
    (SIXTEENTH + C5),
    (EIGTH + E5),
    (EIGTH + G5),       // 50
    (EIGTH + R),
    (EIGTH + G4),
    (EIGTH + R),
    (SIXTEENTH + E5),   // 51
    (EIGTH + C5),
    (SIXTEENTH + G4),
    (EIGTH + R),
    (EIGTH + G4s),
    (SIXTEENTH + A4),   // 52
    (EIGTH + F5),
    (BREAK + R),
    (SIXTEENTH + F5),
    (QUARTER + A4),
    (SIXTEENTH + B4),   // 53
    (EIGTH + A5),
    (BREAK + R),
    (SIXTEENTH + A5),
    (BREAK + R),
    (SIXTEENTH + A5),
    (EIGTH + G5),
    (SIXTEENTH + F5),
    (SIXTEENTH + E5),   // 54
    (EIGTH + C5),
    (SIXTEENTH + A4),
    (QUARTER + G4),
    (SIXTEENTH + E5),   // 55
    (EIGTH + C5),
    (SIXTEENTH + G4),
    (EIGTH + R),
    (SIXTEENTH + G4s),
    (SIXTEENTH + A4),   // 56
    (EIGTH + F5),
    (BREAK + R),
    (SIXTEENTH + F5),
    (QUARTER + A4),
    (SIXTEENTH + B4),   // 57
    (EIGTH + F5),
    (BREAK + R),
    (SIXTEENTH + F5),
    (BREAK + R),
    (SIXTEENTH + F5),
    (EIGTH + E5),
    (SIXTEENTH + D5),
    (QUARTER + C5),     // 58
    (QUARTER + C4),
    (D_EIGTH + C5),     // 59
    (D_EIGTH + G4),
    (EIGTH + E4),
    (SIXTEENTH + A4),   // 60
    (EIGTH + B4),
    (SIXTEENTH + A4),
    (SIXTEENTH + G4s),
    (EIGTH + B4b),
    (SIXTEENTH + A4),
    (HALF + G4)         // 61
};

// global state variables
//----------------------------------
#define DEFAULT_TEMPO   2.25
#define FLASH_INTERVAL  30

unsigned char sys_mod = 2;                  // system state, 0 = playing, 1 = paused, 2 = start of song, 3 = endofsong
unsigned int curr_song_len = SONG1_LENGTH;  // current song length, default to song1
const unsigned char *curr_song = song1;     // defaults to song1, "Joy to the World"
unsigned int duration_counter = 0;          // counts the number of WDT cycles for the current note duration
unsigned int score_counter = 0;             // indexes into the score for each note
unsigned char flash_counter = 0;            // counts the number of WDT cycles per LED flash
float tempo = DEFAULT_TEMPO;                // tempo, initial value 2.5, +/- increments of 0.125
unsigned char isbreak = 0;                  // identifies whether the current note is a break or not


// function prototypes
//----------------------------------
void init_timerA(void);                     // routine to setup timerA (frequency generator)
void init_WDT(void);                        // routine to setup WDT
void init_P1(void);                         // routine to setup the I/O pins of Port 1
void toggle_pause(void);                    // toggle between paused and not-paused
void restart_song(void);                    // reset song from beginning, resets tempo
void increase_tempo(void);                  // increase the song tempo
void decrease_tempo(void);                  // decrease the song tempo
void select_song1(void);                    // select song 1, restart song from beginning
void select_song2(void);                    // select song 2, restart song from beginning

// main
//----------------------------------
void main() {
    BCSCTL1 = CALBC1_1MHZ;    // 1Mhz calibration for SMCLK clock
    DCOCTL  = CALDCO_1MHZ;

    init_P1();
    init_WDT();
    init_timerA();
    restart_song();

    _bis_SR_register(GIE+LPM0_bits);// enable general interrupts and power down CPU
}

// initialization functions
//----------------------------------

// timerA is used as the frequency generator
void init_timerA(void) {

    TA0CTL |= TACLR;        // reset clock
    TA0CTL = (TASSEL_2 +    // clock source = SMCLK
              ID_0 +        // clock divider = 1
              MC_1);        // UP mode
                            // timer A interrupt off
    TA0CCTL0=0;             // compare mode, output 0, no interrupt enabled
}

// WDT is used as the system "conductor"
void init_WDT(void) {

      WDTCTL =  (WDTPW +    // password
                 WDTTMSEL + // select interval timer mode
                 WDTCNTCL + // clear watchdog timer counter
                 0 +        // SMCLK is the source
                 1);        // source/8k

    // enable the WDT interrupt (in the system interrupt register IE1)
    IE1 |= WDTIE;
}

// setup Port 1 GPIO pins
void init_P1(void) {

    P1DIR |= LED;       // LED indicator
    P1OUT |= LED;

    P1SEL |= SPEAKER;   // speaker
    P1DIR |= SPEAKER;

    // All remaining GPIOs are already inputs after reset

    // Reset button:
    // 1x press restarts the song
    // 2x press changes songs
    P1OUT |= RESET_BUTTON;  // pullup
    P1REN |= RESET_BUTTON;  // enable pullup resistor
    P1IES |= RESET_BUTTON;  // set for 1->0 transition
    P1IFG &= ~RESET_BUTTON; // clear interrupt flag
    P1IE  |= RESET_BUTTON;  // enable interrupt

    // Play/Pause button:
    P1OUT |= PLAY_BUTTON;   // pullup
    P1REN |= PLAY_BUTTON;   // enable pullup resistor
    P1IES |= PLAY_BUTTON;   // set for 1->0 transition
    P1IFG &= ~PLAY_BUTTON;  // clear interrupt flag
    P1IE  |= PLAY_BUTTON;   // enable interrupt

    // Slower Tempo button:
    P1OUT |= SLOW_BUTTON;   // pullup
    P1REN |= SLOW_BUTTON;   // enable pullup resistor
    P1IES |= SLOW_BUTTON;   // set for 1->0 transition
    P1IFG &= ~SLOW_BUTTON;  // clear interrupt flag
    P1IE  |= SLOW_BUTTON;   // enable interrupt

    // Faster Tempo button:
    P1OUT |= FAST_BUTTON;   // pullup
    P1REN |= FAST_BUTTON;   // enable pullup resistor
    P1IES |= FAST_BUTTON;   // set for 1->0 transition
    P1IFG &= ~FAST_BUTTON;  // clear interrupt flag
    P1IE  |= FAST_BUTTON;   // enable interrupt

    // Song1 button:
    P1OUT |= SONG1_BUTTON;  // pullup
    P1REN |= SONG1_BUTTON;  // enable pullup resistor
    P1IES |= SONG1_BUTTON;  // set for 1->0 transition
    P1IFG &= ~SONG1_BUTTON; // clear interrupt flag
    P1IE  |= SONG1_BUTTON;  // enable interrupt

    // Song2 button:
    P1OUT |= SONG2_BUTTON;  // pullup
    P1REN |= SONG2_BUTTON;  // enable pullup resistor
    P1IES |= SONG2_BUTTON;  // set for 1->0 transition
    P1IFG &= ~SONG2_BUTTON; // clear interrupt flag
    P1IE  |= SONG2_BUTTON;  // enable interrupt
}

// runtime functions
//----------------------------------

// toggle play/pause
void toggle_pause(void) {

    if (sys_mod != 3) { // don't toggle after end of song

        TACCTL0 ^= OUTMOD_4;    // toggle outmod between 0 and 4
        sys_mod = !sys_mod;

        if (!sys_mod) {
            P1OUT &= ~LED;      // turn LED off when playing
        }
    }
}

// decrease the song's tempo
void decrease_tempo(void) {
    if (tempo < 10.0) { // lower limit
        tempo += 0.125;
    }
}

// increase the song's tempo
void increase_tempo(void) {
    if(tempo > 0.125) { // upper limit
        tempo -= 0.125;
    }
}

// restart current song from the beginning
void restart_song(void) {
    TA0CTL |= TACLR;        // reset clock
    TACCTL0 &= ~OUTMOD_4;   // timer is initially off
    duration_counter = 0;
    score_counter = 0;
    tempo = DEFAULT_TEMPO;  // reset tempo to default
    isbreak = 0;
    sys_mod = 2;
    TA0CCR0 = notes[(curr_song[0] & NOTE_MASK)]-1; // in up mode counts from TAR=0 to TACCRO-1
    P1OUT |= LED;           // steady LED indicates song ready
}

// select song 1, restart song from beginning
void select_song1(void) {
    sys_mod = 2;
    curr_song = song1;
    curr_song_len = SONG1_LENGTH;
    restart_song();
}

// select song 2, restart song from beginning
void select_song2(void) {
    sys_mod = 2;
    curr_song = song2;
    curr_song_len = SONG2_LENGTH;
    restart_song();
}

// interrupt handlers
//----------------------------------

// handles all button interrupts
interrupt void button_handler(void) {

    // check which interrupt occured
    if (P1IFG & RESET_BUTTON) {
        P1IFG &= ~RESET_BUTTON; // reset the interrupt flag
        restart_song();
    }
    else if (P1IFG & PLAY_BUTTON) {
        P1IFG &= ~PLAY_BUTTON;
        // handle the play/pause behavior here
        toggle_pause();
    }
    else if (P1IFG & SLOW_BUTTON) {
        P1IFG &= ~SLOW_BUTTON;
        // handle the slower tempo here
        decrease_tempo();
    }
    else if (P1IFG & FAST_BUTTON) {
        P1IFG &= ~FAST_BUTTON;
        // handle the faster tempo here
        increase_tempo();
    }
    else if (P1IFG & SONG1_BUTTON) {
        P1IFG &= ~SONG1_BUTTON;
        select_song1();
    }
    else if (P1IFG & SONG2_BUTTON) {
        P1IFG &= ~SONG2_BUTTON;
        select_song2();
    }
}

// System Conductor
// called every 1Mhz/8k = once every 8.2ms
interrupt void WDT_interval_handler(void) {

    if (sys_mod == 0) { // playing

        if (score_counter < curr_song_len) {

            if (!isbreak) {
                if (duration_counter >= (durations[(curr_song[score_counter] >> 5)]) * tempo) {
                    // setup next note in the score
                    duration_counter = 0;
                    score_counter++;

                    TA0CCR0 = notes[(curr_song[score_counter] & NOTE_MASK)];

                    if (durations[(curr_song[score_counter] >> 5)] == 1) { // break
                        isbreak = 1;
                    }
                    else {
                        isbreak = 0;
                    }

                }
                else {
                    duration_counter++;
                }
            }
            // last note was a break
            else {
                duration_counter = 0;
                score_counter++;
                TA0CCR0 = notes[(curr_song[score_counter] & NOTE_MASK)];
                isbreak = 0;
            }

        }
        else {
            // stop playing the song (stop TimerA)
            sys_mod = 3;            // end of song
            TACCTL0 &= ~OUTMOD_4;
            P1OUT |= LED;           // steady LED indicates end of song
        }
    }
    else if (sys_mod == 1) { // paused

        // flash LED to indicate paused
        if (flash_counter == FLASH_INTERVAL) {
            flash_counter = 0;
            P1OUT ^= LED;
        }
        else {
            flash_counter++;
        }
    }
}


// declare interrupt handlers
//----------------------------------
ISR_VECTOR(button_handler,".int02")         // declare P1 interrupt handler
ISR_VECTOR(WDT_interval_handler,".int10")   // declare WDT interrupt handler
