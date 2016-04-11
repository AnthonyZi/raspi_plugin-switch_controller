#include "Transmitter.h"

void transmitter_init()
{
        cli();
        TCCR1B |= 1<<WGM12;	//Put Timer/Counter1 in CTC mode
        TIMSK |= 1<<OCIE1A;	//enable timer compare interrupt
        sei();			//Enable global interrupts
        
        //Setup the I/O for the LED
        
        TRANSMITTER_DDR |= (1<<TRANSMITTER_PIN_NUMBER);		//Set PortD Pin0 as an output
        TRANSMITTER_PORT |= (1<<TRANSMITTER_PIN_NUMBER);        //Set PortD Pin0 high to turn on LED
}

void transmitter_sendbit(bool valp)
{
	std::cout << valp;
        switch(valp)
        {
                case 0:
                        TRANSMITTER_PORT |= (1<<TRANSMITTER_PIN_NUMBER);
                        timer1delaymicro(SHORTPAUSE);
                        TRANSMITTER_PORT &= ~(1<<TRANSMITTER_PIN_NUMBER);
                        timer1delaymicro(LONGPAUSE);
                        break;
                case 1:
                        TRANSMITTER_PORT |= (1<<TRANSMITTER_PIN_NUMBER);
                        timer1delaymicro(LONGPAUSE);
                        TRANSMITTER_PORT &= ~(1<<TRANSMITTER_PIN_NUMBER);
                        timer1delaymicro(SHORTPAUSE);
                        break;
                default:
                        break;
        }
}

void transmitter_activate()
{
        TRANSMITTER_PORT |= (1<<TRANSMITTER_PIN_NUMBER);
        timer1delaymilli(1);
}

void transmitter_sendsignal(uint32_t signalp, uint8_t signallengthp)
{
	uint32_t signalcomperator = 1<<(signallengthp-1);
        TRANSMITTER_PORT &= ~(1<<TRANSMITTER_PIN_NUMBER);
        timer1delaymilli(10);
        for(int i = 0; i<signallengthp; i++)
        {
		sendbit( (signalp&signalcomperator) > 0 );
		signalp = signalp<<1;
        }
}

void timer1delaymicro(uint16_t microsecondsp) //maximum 65536 ms
{
        OCR1A = microsendsp;            //set TOP of TIMER1A
        timerinterrupt=0;               //clear timerinterrupt variable
        TCCR1B |= 1<<CS10;	        //start timer with no prescaler
        while(!timerinterrupt) { }
}

void timer1delaymilli(uint16_t millisecondsp) //maximum 16777 ms
{
        OCR1A = (uint16_t)(((uint32_t)millisecondsp*1000)/256); //set TOP of TIMER1A
        timerinterrupt=0;                                       //clear timerinterrupt variable
        TCCR1B |= 1<<CS12;                                      //start timer with prescaler 256
        while(!timerinterrupt) { }
}

//Interrupt Service Routine
ISR(TIMER1_COMPA_vect)
{
        timerinterrupt = 1;                             //awake timer1dleay-functions
        TCCR1B &= ~(1<<CS10) & ~(1<<CS11) & ~(1<<CS12); //stop timer
        TCNT1 = 0;                                      //clear counter for the next usage
}


