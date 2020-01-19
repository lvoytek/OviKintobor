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

#define SCAN_TIME 30

typedef struct BTDataPoint_t
{
    int rssi = 0;
    double gpslat = 0;
    double gpslng = 0;
    float gpsalt = 0;
} BTDataPoint;

typedef struct BTDevice_t
{
    char macAddress[18];
    double lat = 0;
    double lng = 0;
    float alt = 0;
    BTDataPoint dataPoints[4];

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

  void addDevice(const char * addr)
  {
      tail->next = (BTDevice *) malloc(sizeof(BTDevice));
      strncpy(tail->next->macAddress, addr, 17);
  }

  void createDataPoint(BTDataPoint * dp, int rssi, double lat, double lng, float alt)
  {
      dp->rssi = rssi;
      dp->gpslat = lat;
      dp->gpslng = lng;
      dp->gpsalt = alt;
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
            	  this->createDataPoint(this->head->dataPoints, rssi, lat, lng, alt);
    			}
    			else
    			{
    				BTDevice * dev = this->deviceExists(addr);
    				if(dev != NULL)
    					this->createDataPoint(dev->dataPoints, rssi, lat, lng, alt);
    				else
            {
    					this->addDevice(addr);
              this->createDataPoint(this->tail->dataPoints, rssi, lat, lng, alt);
            }
    			}
		}
	}

	void displayDatas()
	{
    BTDevice * temp = this->head;
    while(temp != NULL)
    {
      Serial.print(temp->macAddress);
      Serial.print(": ");
      Serial.println(temp->dataPoints[0].rssi);
    }
	}
};

#endif
