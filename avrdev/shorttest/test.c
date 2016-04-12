#define F_CPU 1000000

#include <avr/io.h>
#include <avr/interrupt.h>

void init(void)
{
        //pin init
        DDRD |= 1<<0;

//        sei();
        SREG |= (1<<7); //set I-bit (Interrupt enable) in SREG
        //counter init
        TCCR1B &= ~(1<<CS10) & ~(1<<CS11) & ~(1<<CS12); //force stop counter
        TIMSK &= ~(1<<TICIE1) & ~(1<<OCIE1A) & ~(1<<OCIE1B) & ~(1<<TOIE1); //disable interrupts (cli() could be used too)
        TIFR |= ~(1<<ICF1) | ~(1<<OCF1A) | ~(1<<OCF1B) | ~(1<<TOV1); // clear interrupts if there were some
//        cli();
        
        //set CTC-mode
        TCCR1B |= (1<<WGM12);
        //set top value for the counter in CTC-mode
        OCR1A = (uint16_t)15624;
        //enable interrupt for tcnt1==ocr1a
        TIMSK |= (1<<OCIE1A);

        //set prescaler to 64 (CSxx) and start counter
        TCCR1B |= (1<<CS11) | (1<<CS10);
//        sei();
}

int main(void)
{
        init();
        PORTD ^= (1<<0);

        while(1)
        {
        }			//Loop forever, interrupts do the rest
}

ISR(TIMER1_COMPA_vect)
{
        PORTD ^= (1<<0);
}
