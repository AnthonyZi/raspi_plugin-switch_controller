#ifndef _transmitter_h
#define _transmitter_h

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

#define SHORTPAUSE      375     //in µs
#define LONGPAUSE       1125    //in µs

#define TRANSMITTER_DDR         DDRD
#define TRANSMITTER_PORT        PORTD
#define TRANSMITTER_PIN_NUMBER  0

void transmitter_init(void);
void transmitter_sendbit(uint8_t valp);
void transmitter_activate(void);	//HI for 1 ms to wake transmitter up

void transmitter_sendsignal(uint32_t signalp, uint8_t signallengthp);

void timer1delaymilli(uint16_t millisecondsp); //maximum 16777 ms
void timer1delaymicro(uint16_t microsecondsp); //maximum 65563 µs

#endif
