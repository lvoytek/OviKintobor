#include "LoRaCommunicator.h"


LoRaCommunicator radio;
char data[255];

void setup() {
  radio.begin();
  Serial.begin(9600);
}

void loop()
{

  if(Serial.available() > 0)
  {
    radio.sendString(Serial.readString().c_str());
  }
 

  if(radio.receiveString(data))
  {
    Serial.println(data);
  }

  delay(50);
}
