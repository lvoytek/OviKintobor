/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 *
 * Author: Lena Voytek
 *
 * LoRaCommunicator.h
 * Sends and receives LoRa messages via a master i2c connection on
 * address 5
 */

#ifndef LORACOMMUNICATOR_H
#define LORACOMMUNICATOR_H

#include <Arduino.h>
#include <Wire.h>

class LoRaCommunicator
{
protected:
    char dataBuffer[255];

public:
    void begin()
    {
        Wire.begin();
    }

    char * receive()
    {
        Wire.requestFrom(5, 15);

        int dataLoc = 0;
        while(Wire.available())
        {
            this->dataBuffer[dataLoc++] = Wire.read();
        }
        return this->dataBuffer;
    }
};

#endif
