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
  Serial.begin(9600);

  //sonic is pretty fast
  frontLeft->setSpeed(200);
  frontRight->setSpeed(200);
  backLeft->setSpeed(200);
  backRight->setSpeed(200);

  //just in case, lets stop them
  frontLeft->run(RELEASE);
  frontRight->run(RELEASE);
  backLeft->run(RELEASE);
  backRight->run(RELEASE);
}

void goForward(){
  frontLeft->run(FORWARD);
  frontRight->run(FORWARD);
  backLeft->run(FORWARD);
  backRight->run(FORWARD);

  delay(250);

  frontLeft->run(RELEASE);
  frontRight->run(RELEASE);
  backLeft->run(RELEASE);
  backRight->run(RELEASE);
}

void goBackward(){
  frontLeft->run(BACKWARD);
  frontRight->run(BACKWARD);
  backLeft->run(BACKWARD);
  backRight->run(BACKWARD);

  delay(250);

  frontLeft->run(RELEASE);
  frontRight->run(RELEASE);
  backLeft->run(RELEASE);
  backRight->run(RELEASE);
}

void turnLeft(){
  frontLeft->run(BACKWARD);
  backLeft->run(BACKWARD);

  delay(250);

  frontLeft->run(RELEASE);
  backLeft->run(RELEASE);
}

void turnRight(){
  frontRight->run(BACKWARD);
  backRight->run(BACKWARD);

  delay(250);

  frontRight->run(RELEASE);
  backRight->run(RELEASE);
}

void loop() {
  if(Serial.available()){
    String command = Serial.readStringUntil('\n');
    
    if(command.equals("{fwd}")){
      Serial.println(command);  
      goForward();
    }
    if(command.equals("{back}")){
      goBackward();
    }
    if(command.equals("{left}")){
      turnLeft();
    }
    if(command.equals("{right}")){
      turnRight();
    }
  }
  delay(50);

}
