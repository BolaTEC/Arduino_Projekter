/*
   Dette program tager mod kommandoer tal -255 til 255 for at styre motor
   minus giver en retning + den anden retning. 0=STOP 255=100% power
*/

//***********************************
//Setup constants
//***********************************
const int enable = 12;
const int left = 11;
const int right = 10;

//***********************************
// Global variable
//***********************************

int incomingByte = 0;   // for incoming serial data
int motorSpeed = 0;
int oldSpeed = 0;
int ledToggle = 0;

void setup() {

  //***********************************
  // Set inout and output pins, set default value
  //***********************************
    pinMode(enable,OUTPUT);
    digitalWrite(enable,LOW);
    
    pinMode(left,OUTPUT);
    analogWrite(left,0);
    pinMode(right,OUTPUT);
    analogWrite(right,0);
    
    ///////////////////////////
    // FOR DEBUG PURPOSES
    pinMode(13, OUTPUT);
    digitalWrite(13, ledToggle);
    ///////////////////////////
    //***********************************
    //Serial connection 9600 Baud
    //***********************************
    Serial.begin(9600);

  }

void loop() {
  // put your main code here, to run repeatedly:
  motorSpeed = readSerial();
  
  // Check if speedchange is nessesary
  if (oldSpeed != motorSpeed)
  {
    if (motorSpeed == 0)
    {
      // Shut down all FETs
      digitalWrite(enable, LOW);
      analogWrite(left, 0);
      analogWrite(right, 0);
    }
    else if (motorSpeed > 0)
    {
      digitalWrite(enable, HIGH);
      analogWrite(left, 0);
      analogWrite(right, motorSpeed);
    }
    else if (motorSpeed < 0)
    {
      digitalWrite(enable, HIGH);
      analogWrite(right, 0);
      analogWrite(left, motorSpeed * -1);
    }
    Serial.println(motorSpeed,DEC);
    
    // Save new speedvalue
    oldSpeed = motorSpeed;
  }
  delay(1000);
  
  // Toogle the LED 13 for livelight
  ledToggle=ledToggle + 1;
  digitalWrite(13,ledToggle%2 );
}

//***********************************
// Read data from UART connection
//***********************************
int readSerial() {
  if (Serial.available() > 1) {
    // read the incoming byte:
    incomingByte = Serial.parseInt();
  }
  return incomingByte;
}
