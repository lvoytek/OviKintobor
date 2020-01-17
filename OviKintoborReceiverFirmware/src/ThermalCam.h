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

    float pixels[AMG88xx_PIXEL_ARRAY_SIZE];

    char pixelSentence[300];
public:
    void begin()
    {
        amg.begin();
        pixelSentence[0] = 'T';
        pixelSentence[1] = ',';
    }

    char * getPixelSentence()
    {
        amg.readPixels(this->pixels);

        char * sentencePtr = this->pixelSentence + 2;
        
        for(int i = 0; i < 7; i++)
        {
            for(int j = 0; j < 7; j++)
            {
                sprintf(sentencePtr, "%d.%02u;", (int) pixels[i*8 + j], (uint8_t) (pixels[i*8 + j] * 100) % 100);
                sentencePtr += strlen(sentencePtr);
            }

            sprintf(sentencePtr, "%d.%02u,", (int) pixels[i*8 + 7], (uint8_t) (pixels[i*8 + 7] * 100) % 100);
            sentencePtr += strlen(sentencePtr);
        }
        sprintf(sentencePtr, "%d.%02u\n", (int) pixels[63], (uint8_t) (pixels[63] * 100) % 100);

        return this->pixelSentence;
    }
};
#endif