/*  
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. 
 * 
 * Author: Lena Voytek
 * 
 * GPSSensor.h
 * Handles interaction with the Serial GPS featherwing on the receiver
 * module
 */

#ifndef GPSSENSOR_H
#define GPSSENSOR_H
#include <TinyGPS++.h>

class GPSSensor
{
protected:
	TinyGPSPlus GPS = TinyGPSPlus();
	TinyGPSCustom gFix = TinyGPSCustom(GPS, "GPGGA", 6);
	char gpsBuffer;
	char sentenceBuffer[256];

public:
	// Configure the GPS for a 9600 baud Serial input
	void begin()
	{
		Serial1.begin(9600);
	}

	/// Get available GPS data from serial for parsing
	void readGPSData()
	{
		while(Serial1.available() > 0) {
			this->gpsBuffer = Serial1.read();
			this->GPS.encode(gpsBuffer);
		}
	}

	// Get the current GPS time as a character array
	// returns: a JSON formatted time statement
	char * getGPSTime()
	{
		snprintf(this->sentenceBuffer, sizeof(this->sentenceBuffer), "{\"day\":%u, \"month\":%u, \"year\":%u, \"hour\":%u, \"minute\":%u, \"second\":%u}", this->GPS.date.day(), this->GPS.date.month(), this->GPS.date.year(), this->GPS.time.hour(), this->GPS.time.minute(), this->GPS.time.second());
		return this->sentenceBuffer;
	}

	// Check if number of available satellites has changed
	boolean satellitesChanged()
	{
		return this->GPS.satellites.isUpdated();
	}

	// Determine the number of connected satellites
	float getSatellites()
	{
		return this->GPS.satellites.value();
	}

	// Get a JSON formatted GPS location/time sentence
	char * getFormattedGPSSentence()
	{
		snprintf(this->sentenceBuffer, sizeof(this->sentenceBuffer), "{\"datetime\":\"%u/%u/%u, %02u:%02u:%02u\", \"lat\":%f, \"lng\":%f, \"altitude\":%f, \"fix\":%s, \"satellites\":%u, \"hdop\":%f}",this->GPS.date.month(),  this->GPS.date.day(), this->GPS.date.year(), this->GPS.time.hour(), this->GPS.time.minute(), this->GPS.time.second(), this->GPS.location.lat(), this->GPS.location.lng(), this->GPS.altitude.meters(), this->gFix.value(), this->GPS.satellites.value(), this->GPS.hdop.value() / 100.0);
		return this->sentenceBuffer;
	}

	//Get the current second of the current time
	uint8_t getGPSSeconds()
	{
		return this->GPS.time.second();
	}
};


#endif