#include <Arduino.h>
#include <Wire.h>
#include <LoRaCommunicator.h>

LoRaCommunicator radio;
char incomingBuffer[255][10];
char outgoing[255];

int outgoingLoc = 0;

int lastMessageLoc = 0;
int firstMessageLoc = 0;

void i2cRecv(int number)
{
	while(Wire.available() && outgoingLoc < 254)
	{
		outgoing[outgoingLoc] = Wire.read();
		if(outgoing[outgoingLoc] == '\0')
		{
			radio.sendString(outgoing);
			outgoingLoc = 0;
		}
	}

	if(outgoingLoc == 254)
	{
		outgoing[outgoingLoc] = '\0';
		radio.sendString(outgoing);
		outgoingLoc = 0;
	}
}

void messageRequest()
{
	if(lastMessageLoc == firstMessageLoc)
		Wire.write('\0');
	
	else
	{
		char * tempChr = incomingBuffer[firstMessageLoc ++];

		while(*tempChr != '\0')
			Wire.write(*tempChr);

		Wire.write('\0');

		firstMessageLoc = firstMessageLoc%10;
	}
	
}

void setup()
{
	Wire.begin(5);
	Wire.onReceive(i2cRecv);
	Wire.onRequest(messageRequest);
	radio.begin();
	
}

void loop()
{

	if(radio.receiveString(incomingBuffer[lastMessageLoc]))
	{
		lastMessageLoc++;
		lastMessageLoc = lastMessageLoc%10;
	}

	delay(25);
}