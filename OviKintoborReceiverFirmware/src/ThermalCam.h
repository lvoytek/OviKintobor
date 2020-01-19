/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 *
 * Author: Lena Voytek
 *
 * ThermalCam.h
 * Handles communication with the 8x8 thermal camera sensor
 */

#ifndef THERMALSENSOR_H
#define THERMALSENSOR_H

#include <Adafruit_AMG88xx.h>

class ThermalCam
{
protected:
    Adafruit_AMG88xx amg;

    float pixels[64];

    char pixelSentence[500];
public:
    void begin()
    {
        amg.begin();
        sprintf(this->pixelSentence, "{\"type\":\"ifr\", \"data\":[[");
    }

    char * getPixelSentence()
    {
        amg.readPixels(this->pixels);

        char * sentencePtr = this->pixelSentence + 24;

        for(int i = 0; i < 8; i++)
        {
            for(int j = 0; j < 7; j++)
            {
                sprintf(sentencePtr, "%.2f,", pixels[i*8 + j]);
                sentencePtr += strlen(sentencePtr);
            }

            sprintf(sentencePtr, "%.2f], [", pixels[i*8 + 7]);
            sentencePtr += strlen(sentencePtr);
        }
        sprintf(sentencePtr - 3, "]]}\n");

        return this->pixelSentence;
    }
};
#endif
