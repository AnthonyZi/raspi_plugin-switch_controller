#include <wiringPi.h>
#include <iostream>
#include <stdint.h>

#define A 0b0111
#define B 0b1011
#define C 0b1101
#define D 0b1110

#define ON 1
#define OFF 0

class ElroSender
{
private:
        bool praeamble[11];
        bool suffixon[6];
        bool suffixoff[6];
        int datapin;

        void init(int pinp, int codep);
        void sendbit(int bitp, int valp);

public:
	ElroSender(int pinp);
	virtual ~ElroSender();
        void sendsignal(uint8_t devicecodep, bool statep);
};
