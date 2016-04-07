#include "Transmitter.h"

#define SIGLENGTH 25
#define B_ON  0b0100010100010001010100010
#define B_OFF 0b0100010100010001010101000
#define END   0b0100010100010101010111110

void bla(Transmitter* trans)
{	
	digitalWrite(1, 1);
	trans->sendsignal(B_ON, SIGLENGTH);
        //delay(10); 
	trans->sendsignal(B_ON, SIGLENGTH);
        //delay(10); 
	trans->sendsignal(B_ON, SIGLENGTH);
        //delay(10); 
	trans->sendsignal(END, SIGLENGTH);
	delay(3000);

	digitalWrite(1, 1);
	trans->sendsignal(B_OFF, SIGLENGTH);
        //delayMicroseconds(10437); 
	trans->sendsignal(B_OFF, SIGLENGTH);
        //delayMicroseconds(10437); 
	trans->sendsignal(B_OFF, SIGLENGTH);
        //delayMicroseconds(10437); 
	trans->sendsignal(END, SIGLENGTH);
	delay(3000);
}

int main()
{
        wiringPiSetup();
	Transmitter* trans = new Transmitter(1);

	while(1)
	{
		bla(trans);
	}
}
