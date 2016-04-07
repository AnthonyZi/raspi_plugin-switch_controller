#include "Transmitter.h"

int main()
{
	Transmitter trans = new Transmitter(1);
	trans.sendsignal(A, ON);
	delay(1000);
	trans.sendsignal(A, OFF);
	delay(1000);
	trans.sendsignal(A, ON);
	delay(1000);
	trans.sendsignal(A, OFF);
	delay(1000);
	trans.sendsignal(A, ON);
	delay(1000);
	trans.sendsignal(A, OFF);
	delay(1000);
	trans.sendsignal(A, ON);
	delay(1000);
	trans.sendsignal(A, OFF);
	delay(1000);
}
