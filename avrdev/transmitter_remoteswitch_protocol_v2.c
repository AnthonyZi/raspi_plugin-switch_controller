#include "remoteswitch.h"

//global variables to avoid multiple definitions while linking
uint32_t sendbuffer = 0;
uint32_t sendbuffer_comperator = 0;
uint8_t sendbuffer_state = 0;

void remoteswitch_init()
{
        cli();
        TCCR1B |= 1<<WGM12;	//Put Timer/Counter1 in CTC mode
        TIMSK |= 1<<OCIE1A;	//enable timer compare interrupt
        sei();			//Enable global interrupts
        
        //Setup the I/O for the LED
        
        TRANSMITTER_DDR |= (1<<TRANSMITTER_PIN_NUMBER);		//Set PortD Pin0 as an output
}

void remoteswitch_sendroutine()
{
        switch(sendbuffer_state)
        {
                case SENDBUFFER_STATE_SENDBIT_1:
                        TRANSMITTER_PORT |= (1<<TRANSMITTER_PIN_NUMBER);

                        if((sendbuffer&sendbuffer_comperator)>0)
                                timer1delaymicro(SHORTPAUSE);
                        else
                                timer1delaymicro(LONGPAUSE);

                        sendbuffer_state=SENDBUFFER_STATE_SENDBIT2;
                        break;

                case SENDBUFFER_STATE_SENDBIT_2:
                        TRANSMITTER_PORT &= ~(1<<TRANSMITTER_PIN_NUMBER);

                        if((sendbuffer&sendbuffer_comperator)>0)
                                timer1delaymicro(LONGPAUSE);
                        else
                                timer1delaymicro(SHORTPAUSE);

                        sendbuffer_state=SENDBUFFER_STATE_SENDBIT_1;
                        sendbuffer_comperator >>= 1;
                        sendbuffer_pending--;
                        break;

                case SENDBUFFER_STATE_TRANSMITTER_ACTIVATION_1:
                        TRANSMITTER_PORT |= (1<<TRANSMITTER_PIN_NUMBER);
                        sendbuffer_state = SENDBUFFER_STATE_TRANSMITTER_ACTIVATION_2;
                        timer1delaymilli(1);
                        break;

                case SENDBUFFER_STATE_TRANSMITTER_ACTIVATION_2:
                        TRANSMITTER_PORT &= ~(1<<TRANSMITTER_PIN_NUMBER);
                        sendbuffer_state = SENDBUFFER_STATE_SENDBIT_1:
                        timer1delaymilli(10);
                        break;

                default:
                        break;
        }
}

void remoteswitch_sendsignal(uint8_t switch_no, uint8_t state)
{
        //fill sendbuffer
        uint32_t signal = PREAMBLE;
        switch(switch_no)
        {
                case REMOTESWITCH_A:
                        signal |= A;
                        break;

                case REMOTESWITCH_B:
                        signal |= B;
                        break;

                case REMOTESWITCH_C:
                        signal |= C;
                        break;

                case REMOTESWITCH_D:
                        signal |= D;
                        break;

                default:
                        break;
        }
        if(state==REMOTESWITCH_ON)
                signal |= ON;
        else
                signal |= OFF;

        sendbuffer = signal;

        //send first package
        sendbuffer_comperator = 1UL<<(signallengthp-1);
        sendbuffer_state = SENDBUFFER_STATE_TRANSMITTER_ACTIVATION_1;

        sendroutine();
        
        //send second and third package
        sendbuffer_comperator = 1UL<<(signallengthp-1);
        sendbuffer_state = SENDBUFFER_STATE_SENDBIT_1;
        sendroutine();
        sendbuffer_comperator = 1UL<<(signallengthp-1);
        sendbuffer_state = SENDBUFFER_STATE_SENDBIT_1;
        sendroutine();

        //send end-package
        sendbuffer_comperator = 1UL<<(signallengthp-1);
        sendbuffer_state = SENDBUFFER_STATE_SENDBIT_1;
        sendbuffer = PREAMBLE|END;
        sendroutine();
}

void timer1delaymicro(uint16_t microsecondsp) //maximum 65536 ms
{
        OCR1A = microsecondsp;            //set TOP of TIMER1A
        timerinterrupt = 0;               //clear timerinterrupt variable
        TCCR1B |= 1<<CS10;	        //start timer with no prescaler
}

void timer1delaymilli(uint16_t millisecondsp) //maximum 16777 ms
{
        OCR1A = (uint16_t)(((uint32_t)millisecondsp*1000)/256); //set TOP of TIMER1A
        timerinterrupt = 0;             //clear timerinterrupt variable
        TCCR1B |= 1<<CS12;              //start timer with prescaler 256
}

//Interrupt Service Routine
ISR(TIMER1_COMPA_vect)
{
        TCCR1B &= ~(1<<CS10) & ~(1<<CS11) & ~(1<<CS12); //stop timer
        TCNT1 = 0; //clear counter for the next usage
        if(sendbuffer_comperator>0)
                sendroutine();
}
