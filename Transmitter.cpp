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

//void Transmitter::sendbit(bool valp, std::vector<uint32_t>* timevector)
void Transmitter::sendbit(bool valp)
{
	std::cout << valp;
        switch(valp)
        {
                case 0:
                        digitalWrite(datapin, 1);
                        delayMicroseconds(SHORTPAUSE); 
//			timevector->push_back((uint32_t)micros());
                        digitalWrite(datapin, 0);
                        delayMicroseconds(LONGPAUSE);
//			timevector->push_back((uint32_t)micros());
                        break;
                case 1:
                        digitalWrite(datapin, 1);
                        delayMicroseconds(LONGPAUSE);
//			timevector->push_back((uint32_t)micros());
                        digitalWrite(datapin, 0);
                        delayMicroseconds(SHORTPAUSE);
//			timevector->push_back((uint32_t)micros());
                        break;
                default:
                        break;
        }
}

void Transmitter::sendsignal(uint32_t signalp, uint8_t signallengthp)
{
//	std::vector<uint32_t> timevector;
	uint32_t signalcomperator = 1<<(signallengthp-1);
	digitalWrite(datapin, 0);
	delay(10);
        for(int i = 0; i<signallengthp; i++)
        {
//		sendbit(((signalp&signalcomperator) > 0), &timevector);
		sendbit( (signalp&signalcomperator) > 0 );
		signalp = signalp<<1;
        }
//	int greatestval1=0, greatestval2=0;
//	int lowestval1=600, lowestval2=1400;
//	for(unsigned int i = 1; i<timevector.size(); i++)
//	{
//		int val = (int)(timevector[i]-timevector[i-1]);
//		greatestval1 < val && val < 900 ? greatestval1=val : (greatestval2 < val ? greatestval2=val : val=val);
//		lowestval2 > val && val > 700 ? lowestval2=val : (lowestval1 > val ? lowestval1=val : val=val);
//		std::cout << (int)(timevector[i]-timevector[i-1]) << "   ";
//	}
	std::cout << std::endl;
//	std::cout << lowestval1 << "  " << greatestval1 << " --- " << lowestval2 << "  " << greatestval2 << std::endl;
}
