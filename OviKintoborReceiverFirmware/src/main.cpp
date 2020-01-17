/*  
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. 
 * 
 * Author: Lena Voytek
 * 
 * main.cpp
 * Handles all sensor interaction and communication on the receiver 
 * module
 */

#include <Arduino.h>
#include <GPSSensor.h>
#include <ThermalCam.h>
#include <BluetoothSniffer.h>

GPSSensor gps;
ThermalCam cam;
BluetoothSniffer sniffy;

void setup()
{
	Serial.begin(9600);
    gps.begin();
	cam.begin();
	sniffy.begin();
	delay(1000);
}

void loop()
{
	
	gps.readGPSData();
	Serial.println(cam.getPixelSentence());
	Serial.print(gps.getFormattedGPSSentence());
	delay(1000);
}