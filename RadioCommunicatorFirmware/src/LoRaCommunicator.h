/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 *
 * Author: Lena Voytek
 *
 * LoRaCommunicator.h
 * Handles sending and receiving of radio info over 915MHz LoRa radio
 */

#ifndef LORACOMMUNICATOR_H
#define LORACOMMUNICATOR_H

#define RADIO_CSPIN 8 //The Circuit Select Pin used to toggle SPI Comms On/Off
#define RFM95_CS 8 //Radio chipset pin
#define RFM95_RST 4 //Radio reset pin
#define RFM95_INT 3 //Radio SPI pin

#include <RH_RF95.h>


class LoRaCommunicator
{
protected:
    RH_RF95 rf95 = RH_RF95(RFM95_CS, RFM95_INT);

    float frequency = 915.5;

    void CSEnable(boolean enable)
	{
		if(enable)
			digitalWrite(RADIO_CSPIN, LOW);	//Drop LOW to enable SPI Comms
		else
			digitalWrite(RADIO_CSPIN, HIGH); //Set HIGH to disable SPI Comms
	}

public:
    void begin()
    {
        pinMode(RADIO_CSPIN, OUTPUT);
        digitalWrite(RADIO_CSPIN, LOW);
        pinMode(LED_BUILTIN, OUTPUT);

        pinMode(RFM95_RST, OUTPUT);

    		// Reset the Radio
    		digitalWrite(RFM95_RST, HIGH);
    		delay(1000);
    		digitalWrite(RFM95_RST, LOW);
    		delay(10);
    		digitalWrite(RFM95_RST, HIGH);
    		delay(10);

        this->rf95.init();
        this->rf95.setFrequency(this->frequency);
        this->rf95.setTxPower(23, false);
        digitalWrite(LED_BUILTIN, LOW);
    }

    void sendString(const char * str)
    {
        digitalWrite(LED_BUILTIN, HIGH);
        this->rf95.send((byte *) str, strlen(str) + 1);
        this->rf95.waitPacketSent();
        digitalWrite(LED_BUILTIN, LOW);
        Serial.println(str);
    }

    bool receiveString(char * output)
    {
        uint8_t len;
        bool received = this->rf95.recv((byte *) output, &len);

        return received;
    }
};

#endif
