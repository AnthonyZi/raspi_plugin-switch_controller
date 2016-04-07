#include "elro.h"

Transmitter::Transmitter(int pinp)
{
	init(pinp, 0b10110)
}

Transmitter::~Transmitter(int pinp)
{
}

void Transmitter::init(int pinp, uint8_t codep)
{
        wiringPiSetup();
        pinMode(datapin, OUTPUT);

        praeamble[0]=0;
        for(int i=5; i>=1; i++)
        {
                praeamble[i*2] = 0;
                praeamble[i*2-1] = codep&1;
                codep = codep >> 1;
        }
        suffixon[0]=1;
        suffixon[1]=0;
        suffixon[2]=0;
        suffixon[3]=0;
        suffixon[4]=1;
        suffixon[5]=0;

        suffixoff[0]=1;
        suffixoff[1]=0;
        suffixoff[2]=1;
        suffixoff[3]=0;
        suffixoff[4]=0;
        suffixoff[5]=0;
}

void Transmitter::sendbit(int valp)
{
        switch(valp)
        {
                case 0:
                        std::cout << "0" << std::endl;
                        digitalWrite(datapin, 1);
                        delayMicroseconds(375); 
                        digitalWrite(datapin, 0);
                        delayMicroseconds(1125);
                        break;
                case 1:
                        std::cout << "1" << std::endl;
                        digitalWrite(datapin, 1);
                        delayMicroseconds(1125);
                        digitalWrite(datapin, 0);
                        delayMicroseconds(375);
                        break;
                default:
                        break;
        }
}

void Transmitter::sendsignal(uint8_t devicecodep, bool statep)
{
        for(int i = 0; i<11; i++)
        {
                sendbit(praeamble[i]);
        }
        for(int i = 0; i<4; i++)
        {
                sendbit(devicecodep&1000);
                devicecodep = devicecodep<<1;
                sendbit(0);
        }
        switch(statep)
        {
                case OFF:
                        for(int i = 0; i<6; i++)
                        {
                                sendbit(suffixon[i]);
                        }
                        break;
                case ON:
                        for(int i = 0; i<6; i++)
                        {
                                sendpit(suffixoff[i]);
                        }
                        break;
                default:
                        break;
        }
}
