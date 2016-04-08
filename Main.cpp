#include "Transmitter.h"

/*
 * #define SIGLENGTH 25
 * #define PREAMBLE	0b01000101000 00000000 000000
 * #define A		0b00000000000 00101010 000000
 * #define B		0b00000000000 10001010 000000
 * #define C		0b00000000000 10100010 000000
 * #define D		0b00000000000 10101000 000000
 * #define ON		0b00000000000 00000000 100010
 * #define OFF		0b00000000000 00000000 101000
 * #define END		0b00000000000 10101010 111110
 */

#define SIGLENGTH 25
#define PREAMBLE	0b0100010100000000000000000
#define A		0b0000000000000101010000000
#define B		0b0000000000010001010000000
#define C		0b0000000000010100010000000
#define D		0b0000000000010101000000000
#define ON		0b0000000000000000000100010
#define OFF		0b0000000000000000000101000
#define END		0b0000000000010101010111110

void send(Transmitter* trans, uint32_t sigp)
{	
	digitalWrite(1, 1);
	trans->sendsignal(sigp, SIGLENGTH);
	trans->sendsignal(sigp, SIGLENGTH);
	trans->sendsignal(sigp, SIGLENGTH);
	trans->sendsignal((PREAMBLE|END), SIGLENGTH);
}

int main(int argc, char** argv)
{
	if(argc<3)
	{
		std::cout << "please use command as follows:" << std::endl << "remote_switch DEVICE ON/OFF" << std::endl;
		return 1;
	}

	uint32_t sendsequence = PREAMBLE; 
	if(argv[1] == std::string("A"))
		sendsequence |= A;
	else if(argv[1] == std::string("B"))
		sendsequence |= B;
	else if(argv[1] == std::string("C"))
		sendsequence |= C;
	else if(argv[1] == std::string("D"))
		sendsequence |= D;
	else
		return 1;

	if(argv[2] == std::string("ON"))
		sendsequence |= ON;
	else if(argv[2] == std::string("OFF"))
		sendsequence |= OFF;
	else
		return 1;


        wiringPiSetup();
	Transmitter* trans = new Transmitter(1);

	send(trans, sendsequence);
}
