#include <msp430g2553.h>

/*
 * SPI Transmitter and ADC Converter
 * ---------------------------------
 * Carlton Duffett
 * Neeraj Basu
 *
 * Converts an analog voltage to a digital value using the ADC. Whenever a conversion is
 * complete, the digital value is transmitted as a byte across the SPI interface to a
 * second Receiver microcontroller.
 */

// Define bit masks for ADC pin and channel used as P1.4
#define ADC_INPUT_BIT_MASK 0x10
#define ADC_INCH INCH_4

// Bit positions in P1 for SPI
#define SPI_CLK 0x20
#define SPI_SOMI 0x40
#define SPI_SIMO 0x80

// SPI interface definitions
#define ACTION_INTERVAL 1
#define BIT_RATE_DIVISOR 32

// Global variables that store the results (read from the debugger)
volatile unsigned long conversion_count  =0;//total number of conversions done
volatile unsigned char data_to_send = 0;    // current byte to transmit
volatile unsigned long tx_count = 0;        // total number of transmissions
volatile unsigned int action_counter = ACTION_INTERVAL;

// ===== Initialization Functions =====
void init_adc(void);
void init_spi(void);
void init_wdt(void);

// ===== Main Program =====
void main(){

    WDTCTL = WDTPW + WDTHOLD;       // Stop watchdog timer
    BCSCTL1 = CALBC1_8MHZ;          // 8Mhz calibration for clock
    DCOCTL  = CALDCO_8MHZ;

    init_adc();
    init_spi();
    init_wdt();

    _bis_SR_register(GIE+LPM0_bits);
}

// ===== Initialize the ADC =====
void init_adc(){

    ADC10CTL1 = ADC_INCH            // input channel 4
              +SHS_0                // use ADC10SC bit to trigger sampling
              +ADC10DIV_4           // ADC10 clock/5
              +ADC10SSEL_0          // Clock Source=ADC10OSC
              +CONSEQ_0;            // single channel, single conversion
              ;
    ADC10AE0 = ADC_INPUT_BIT_MASK;  // enable A4 analog input
    ADC10CTL0 = SREF_0              // reference voltages are Vss and Vcc
              +ADC10SHT_3           // 64 ADC10 Clocks for sample and hold time (slowest)
              +ADC10ON              // turn on ADC10
              +ENC                  // enable (but don't start) conversions
              +ADC10IE              // enable interrupts
              ;
}

// ===== Initialize the Watchdog Timer =====
void init_wdt(){

    // setup the watchdog timer as an interval timer
    WDTCTL =(WDTPW +        // (bits 15-8) password
                            // bit 7=0 => watchdog timer on
                            // bit 6=0 => NMI on rising edge (not used here)
                            // bit 5=0 => RST/NMI pin does a reset (not used here)
             WDTTMSEL +     // (bit 4) select interval timer mode
             WDTCNTCL       // (bit 3) clear watchdog timer counter
                            // bit 2=0 => SMCLK is the source
                            // bits 1-0 = 00 => source/32K
             );
     IE1 |= WDTIE;          // enable the WDT interrupt (in the system interrupt register IE1)
 }

 // calculate the lo and hi bytes of the bit rate divisor
 #define BRLO (BIT_RATE_DIVISOR &  0xFFFF)
 #define BRHI (BIT_RATE_DIVISOR / 0x10000)

// ===== Initialize the SPI Interface =====
void init_spi(){

    UCB0CTL1 = UCSSEL_2+UCSWRST;    // Reset state machine; SMCLK source;
    UCB0CTL0 = UCCKPH               // Data capture on rising edge
                                    // read data while clock high
                                    // lsb first, 8 bit mode,
            +UCMST                  // master
            +UCMODE_0               // 3-pin SPI mode
            +UCSYNC;                // sync mode (needed for SPI or I2C)
    UCB0BR0 = BRLO;                 // set divisor for bit rate
    UCB0BR1 = BRHI;
    UCB0CTL1 &= ~UCSWRST;           // enable UCB0 (must do this before setting
                                    //              interrupt enable and flags)
    IFG2 &= ~UCB0RXIFG;             // clear UCB0 RX flag
    IE2 |= UCB0RXIE;                // enable UCB0 RX interrupt

    // Connect I/O pins to UCB0 SPI
    P1SEL  = SPI_CLK + SPI_SOMI + SPI_SIMO;
    P1SEL2 = SPI_CLK + SPI_SOMI + SPI_SIMO;
}

// ===== ADC Conversion Handler =====
void interrupt adc_handler(){

    // Whenever an ADC conversion completes, store the result
    data_to_send = (unsigned char) ADC10MEM;
    ++conversion_count;
}
ISR_VECTOR(adc_handler, ".int05")

// ===== Watchdog Timer Interrupt Handler =====
interrupt void WDT_interval_handler(){

       ADC10CTL0 |= ADC10SC;  // trigger an ADC conversion

       if (--action_counter == 0){

           // Transmit the newest conversion value over SPI
           UCB0TXBUF = data_to_send;    // init sending current byte
           ++tx_count;
           action_counter = ACTION_INTERVAL;
       }
}
ISR_VECTOR(WDT_interval_handler, ".int10")

// ===== SPI Receive Handler ====
void interrupt spi_rx_handler(){

    // Reset the SPI interface for the next
    // transmit/receive session
    IFG2 &= ~UCB0RXIFG;      // clear UCB0 RX flag
}
ISR_VECTOR(spi_rx_handler, ".int07")
