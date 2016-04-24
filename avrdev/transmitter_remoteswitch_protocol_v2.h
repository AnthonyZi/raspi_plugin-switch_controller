#ifndef _transmitter_h_v2
#define _transmitter_h_v2

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

#define SHORTPAUSE      375     //in µs
#define LONGPAUSE       1125    //in µs

#define TRANSMITTER_DDR         DDRD
#define TRANSMITTER_PORT        PORTD
#define TRANSMITTER_PIN_NUMBER  0

#define SENDBUFFER_STATE_SENDBIT_1 10
#define SENDBUFFER_STATE_SENDBIT_2 11
#define SENDBUFFER_STATE_TRANSMITTER_ACTIVATION_1 0
#define SENDBUFFER_STATE_TRANSMITTER_ACTIVATION_2 1

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


void remoteswitch_init(void);
void remoteswitch_sendroutine(uint8_t valp);

void remoteswitch_sendsignal(uint32_t signalp, uint8_t signallengthp);

void timer1delaymilli(uint16_t millisecondsp); //maximum 16777 ms
void timer1delaymicro(uint16_t microsecondsp); //maximum 65563 µs

#endif
