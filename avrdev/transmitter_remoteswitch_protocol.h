#ifndef _transmitter_h
#define _transmitter_h

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

#define TIMEUNIT        375     //µs
#define SHORTPAUSE      1       //multiple of timeunit
#define LONGPAUSE       3       //multiple of timeunit

#define TRANSMITTER_DDR         DDRD
#define TRANSMITTER_PORT        PORTD
#define TRANSMITTER_PIN_NUMBER  0

uint8_t datapin = 0;
bool timeinterrupt = 0;

void transmitter_init();
void transmitter_sendbit(bool valp);
void transmitter_activate()      //HI for 1 ms to wake transmitter up

void transmitter_sendsignal(uint32_t signalp, uint8_t signallengthp);

void timer1delaymilli(uint16_t millisecondsp);
void timer1delaymicro(uint16_t microsecondsp);

#endif
