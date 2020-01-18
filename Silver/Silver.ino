

void setup() {
  Serial.begin(9600);

}

//Reads any inputs that may come in over serial
void readFromSerial(){
  char inputStr[255];
  int index = 0;
  bool done;
  
  while (true){
    done = false;

    while(!done){
      while(Serial.available() > 0){ //Incoming communications
        char inputChar = Serial.read();
        if (inputChar == '\n') { //It's not over til the newline
          done = true;                
          if(index < 255){
            inputStr[index] = '\0';
          }
        } 
        else {
          if (index < 255) { //We don't want to exceed the array size
            inputStr[index] = inputChar;                  
            index++;
          }
        }
      }     
    }

    //Ensure the incoming message is properly formatted. If so, move the arm.
    if (inputStr[0] == 'I') {  
      Serial.println(inputStr);
      return;
    }
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  readFromSerial();
}
