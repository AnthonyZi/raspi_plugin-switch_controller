#include "elrosender.h"

int main()
{
	ElroSender sender = new ElroSender(1);
	sender.sendsignal(A, ON);
	delay(1000);
	sender.sendsignal(A, OFF);
	delay(1000);
	sender.sendsignal(A, ON);
	delay(1000);
	sender.sendsignal(A, OFF);
	delay(1000);
	sender.sendsignal(A, ON);
	delay(1000);
	sender.sendsignal(A, OFF);
	delay(1000);
	sender.sendsignal(A, ON);
	delay(1000);
	sender.sendsignal(A, OFF);
	delay(1000);
}
