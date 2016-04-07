#include <wiringPi.h>
#include <iostream>
#include <stdint.h>

class Transmitter
{
private:
        int datapin;

        void initgpio(int pinp);
        void sendbit(bool valp);

public:
	Transmitter(int pinp);
	virtual ~Transmitter();
        void sendsignal(uint32_t signalp, uint8_t signallengthp);
};
