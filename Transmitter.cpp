#include "Transmitter.h"

Transmitter::Transmitter(int pinp) : datapin(pinp)
{
	initgpio(datapin);
}

Transmitter::~Transmitter()
{
}

void Transmitter::initgpio(int pinp)
{
        pinMode(pinp, OUTPUT);
}

void Transmitter::sendbit(bool valp)
{
	std::cout << valp;
        switch(valp)
        {
                case 0:
                        digitalWrite(datapin, 1);
                        delayMicroseconds(375); 
                        digitalWrite(datapin, 0);
                        delayMicroseconds(1125);
                        break;
                case 1:
                        digitalWrite(datapin, 1);
                        delayMicroseconds(1125);
                        digitalWrite(datapin, 0);
                        delayMicroseconds(375);
                        break;
                default:
                        break;
        }
}

void Transmitter::sendsignal(uint32_t signalp, uint8_t signallengthp)
{
	uint32_t signalcomperator = 1<<(signallengthp-1);
	digitalWrite(datapin, 0);
	delay(10);
        for(int i = 0; i<signallengthp; i++)
        {
		sendbit((signalp&signalcomperator) > 0);
		signalp = signalp<<1;
        }
	std::cout << std::endl;
}
