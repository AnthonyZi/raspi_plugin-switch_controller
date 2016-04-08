#include <wiringPi.h>
#include <iostream>
#include <stdint.h>
#include <vector>

#define SHORTPAUSE 375
#define LONGPAUSE 1125

class Transmitter
{
private:
        int datapin;

        void initgpio(int pinp);
        void sendbit(bool valp);
//        void sendbit(bool valp, std::vector<uint32_t>* timevector);

public:
	Transmitter(int pinp);
	virtual ~Transmitter();
        void sendsignal(uint32_t signalp, uint8_t signallengthp);
};
