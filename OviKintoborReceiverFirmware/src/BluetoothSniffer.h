/*  
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. 
 * 
 * Author: Lena Voytek
 * 
 * BluetoothSniffer.h
 * Uses the ESP32 BLE Module to check for bluetooth devices in the area
 * while collecting enough data to triangulate their position
 */

#ifndef BLUETOOTHSNIFFER_H
#define BLUETOOTHSNIFFER_H

#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>

#define SCAN_TIME 10

typedef struct BTDataPoint_t
{
    int rssi;
    double gpslat;
    double gpslng;
    float gpsalt;
    BTDataPoint_t * nextDataPoint;
} BTDataPoint;

typedef struct BTDevice_t
{
    char macAddress[18];
    double lat;
    double lng;
    float alt;
    BTDataPoint * dataPoints;

    BTDevice_t * next;
} BTDevice;

class AdvertisedDeviceCallbacks : public BLEAdvertisedDeviceCallbacks
{
	void onResult(BLEAdvertisedDevice advertisedDevice)
	{
		Serial.printf("Advertised Device: %s \n", advertisedDevice.toString().c_str());
	}
};

class BluetoothSniffer
{
protected:
	BTDevice * head = NULL;
	BTDevice * tail = NULL;

    void addDevice(const char * addr, BTDataPoint * firstData)
    {
        tail->next = (BTDevice *) malloc(sizeof(BTDevice));
        strncpy(tail->next->macAddress, addr, 17);
        tail->next->dataPoints = firstData;
    }

    BTDataPoint * createDataPoint(int rssi, double lat, double lng, float alt)
    {
        BTDataPoint * dp = (BTDataPoint *) malloc(sizeof(BTDataPoint));
        dp->rssi = rssi;
        dp->gpslat = lat;
        dp->gpslng = lng;
        dp->gpsalt = alt;
        dp->nextDataPoint = NULL;

        return dp;
    }

    void addDataPoint(BTDevice * device, BTDataPoint * data)
    {
        BTDataPoint * tempDP = device->dataPoints;
        
        while(tempDP->nextDataPoint != NULL)
            tempDP = tempDP->nextDataPoint;

        tempDP -> nextDataPoint = data;
    }

	BTDevice * deviceExists(const char * addr)
	{
		BTDevice * tempDevice = this->head;

		while(tempDevice != NULL)
		{
			if(strcmp(addr, tempDevice->macAddress) == 0)
				return tempDevice;

			tempDevice = tempDevice->next;
		}

		return NULL;
	}

public:
    void begin()
    {
        BLEDevice::init("");

    }

    void scan(double lat, double lng, float alt)
    {
        BLEScan *pBLEScan = BLEDevice::getScan(); //create new scan
        pBLEScan->setAdvertisedDeviceCallbacks(new AdvertisedDeviceCallbacks());
        pBLEScan->setActiveScan(true); //active scan uses more power, but get results faster
        pBLEScan->setInterval(0x50);
        pBLEScan->setWindow(0x30);
		
		BLEScanResults foundDevices = pBLEScan->start(SCAN_TIME);
		int count = foundDevices.getCount();

		for (int i = 0; i < count; i++)
		{
			BLEAdvertisedDevice d = foundDevices.getDevice(i);
			const char * addr = d.getAddress().toString().c_str();
			int rssi = d.getRSSI();

			//No devices currently
			if(this->head == NULL)
			{
				this->head = (BTDevice *) malloc(sizeof(BTDevice));
        		strncpy(this->head->macAddress, addr, 17);
        		this->head->dataPoints = this->createDataPoint(rssi, lat, lng, alt);
			}
			else
			{
				BTDevice * dev = this->deviceExists(addr);
				if(dev != NULL)
					this->addDataPoint(dev, this->createDataPoint(rssi, lat, lng, alt));
				else
					this->addDevice(addr, this->createDataPoint(rssi, lat, lng, alt));
			}
			
		}
	}

	void displayDatas()
	{
		
	}
};

#endif