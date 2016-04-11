#include "transmitter_remoteswitch_protocol.h"
#include <avr/io.h>
#include <avr/interrupt.h>

//known signals for a remote_switch
/*
 * #define SIGLENGTH 25
 * #define PREAMBLE	0b01000101000 00000000 000000
 * #define A		0b00000000000 00101010 000000
 * #define B		0b00000000000 10001010 000000
 * #define C		0b00000000000 10100010 000000
 * #define D		0b00000000000 10101000 000000
 * #define ON		0b00000000000 00000000 100010
 * #define OFF		0b00000000000 00000000 101000
 * #define END		0b00000000000 10101010 111110
 */

#define SIGLENGTH 25
#define PREAMBLE	0b0100010100000000000000000
#define A		0b0000000000000101010000000
#define B		0b0000000000010001010000000
#define C		0b0000000000010100010000000
#define D		0b0000000000010101000000000
#define ON		0b0000000000000000000100010
#define OFF		0b0000000000000000000101000
#define END		0b0000000000010101010111110


void remote_switch(uint8_t switch_no, uint8_t state)
{
        uint32_t signal = 0;
        switch(switch_no)
        {
                case 1:
                        signal |= PREAMBLE | A;
                        break;
                case 2:
                        signal |= PREAMBLE | B;
                        break;
                case 3:
                        signal |= PREAMBLE | C;
                        break;
                case 4:
                        signal |= PREAMBLE | D;
                        break;
                default:
                        break;

        }
        (state==1) ? (signal |= ON) : (signal |= OFF);

        transmitter_activate();
        transmitter_sendsignal(signal, SIGLENGTH);
        transmitter_sendsignal(signal, SIGLENGTH);
        transmitter_sendsignal(signal, SIGLENGTH);
        transmitter_sendsignal(PREAMBLE | END, SIGLENGTH);
}

int main(void)
{
        transmitter_init();
        while(1)
        {
               timer1delaymilli(10000);
               remote_switch(1, 0);
        }			//Loop forever, interrupts do the rest
}

ISR(INT1_vect)
{
        remote_switch(1, 1);
}
