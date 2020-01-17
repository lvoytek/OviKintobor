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
#include <Tasker.h>
#include <GPSSensor.h>
#include <ThermalCam.h>
#include <BluetoothSniffer.h>

#define TASKER_MAX_TASKS 18

Tasker tasker(true);

GPSSensor gps;
ThermalCam cam;
BluetoothSniffer sniffy;

void runBLEScan(int)
{
	gps.readGPSData();
	sniffy.scan(gps.getLat(), gps.getLng(), gps.getAlt());
}

void getGPSUpdate(int)
{
	gps.readGPSData();
	Serial.println(gps.getFormattedGPSSentence());
}

void getIRUpdate(int)
{
	Serial.println(cam.getPixelSentence());
}

void setup()
{
	Serial.begin(9600);
    gps.begin();
	cam.begin();
	sniffy.begin();
	delay(1000);

	tasker.setInterval(runBLEScan, 40000, 0);
	tasker.setInterval(getGPSUpdate, 3000, 1);
	tasker.setInterval(getIRUpdate, 5000, 1);

	tasker.run();
}

void loop(){}