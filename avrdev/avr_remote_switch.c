#include "remoteswitch.h"
#include <avr/io.h>
#include <avr/interrupt.h>

int main(void)
{
        transmitter_init();

        uint32_t signal = 0;

        while(1) //Loop forever, interrupts do the rest
        {
               remote_switch(1, 1);
               timer1delaymilli(2000);
               remote_switch(2, 1);
               timer1delaymilli(2000);
               remote_switch(3, 1);
               timer1delaymilli(2000);
               remote_switch(4, 1);
               timer1delaymilli(2000);

               remote_switch(1, 0);
               timer1delaymilli(2000);
               remote_switch(2, 0);
               timer1delaymilli(2000);
               remote_switch(3, 0);
               timer1delaymilli(2000);
               remote_switch(4, 0);
               timer1delaymilli(2000);
        }
}

ISR(INT1_vect)
{
        remote_switch(1, 1);
}
