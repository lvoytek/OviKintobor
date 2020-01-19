/*
 * Movin' around at the speed of sound, this little guy'll be your eyes from the ground. 
 * This program handles the movements of Sonic (the car form for our hack).
 * Commands come in via bluetooth, and an Adafruit Motor FeatherWing is used to 
 * 
 * Author: Lucas Boje
 */

#include <Wire.h>
#include <Adafruit_MotorShield.h>

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 

Adafruit_DCMotor *frontLeft = AFMS.getMotor(1);
Adafruit_DCMotor *frontRight = AFMS.getMotor(2);
Adafruit_DCMotor *backLeft = AFMS.getMotor(3);
Adafruit_DCMotor *backRight = AFMS.getMotor(4);


void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
