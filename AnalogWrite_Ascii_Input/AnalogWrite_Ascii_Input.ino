/*
   Dette program tager mod kommandoer tal 0 til 255 for at styre en
   motors omdrejninger ved hjælp af PWM  0=STOP 128 = 50% power 255=100% power
*/

//***********************************
//Setup constants
//***********************************
const int pwm = 6;

//***********************************
// Global variable
//***********************************
int motorSpeed = 0;
int oldSpeed = 0;
int ledToggle = 0;

void setup() {
  //***********************************
  // Set inout and output pins, set default value
  //***********************************
    pinMode(pwm,OUTPUT);
    analogWrite(pwm,0);

    
    ///////////////////////////
    // FOR DEBUG PURPOSES
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, ledToggle);

    ///////////////////////////
    //***********************************
    //Serial connection 9600 Baud
    //***********************************
    Serial.begin(9600);
    Serial.println("Ready");
  }

void loop() {
  // put your main code here, to run repeatedly:
  motorSpeed = readSerial();
  
  // Check if speedchange is nessesary
  if ((oldSpeed != motorSpeed)&&(motorSpeed != -99))
  {
    if (motorSpeed == 0)
    {
      // Shut down pwm
      analogWrite(pwm,0);
    }
    else if ((motorSpeed > 0)&&(motorSpeed<256))
    {
      Serial.println(motorSpeed,DEC);
      analogWrite(pwm, motorSpeed);
    }
    else
    {
      Serial.println("Please input pwn between 0 and 255");
    }
    // Save new speedvalue
    oldSpeed = motorSpeed;
  }
  delay(1000);
  
  // Toogle the LED 13 for livelight
  ledToggle=ledToggle + 1;
  digitalWrite(LED_BUILTIN,ledToggle%2 );
}

//***********************************
// Read data from UART connection
//***********************************
int readSerial()
{
  int incomingByte=-99;
  if (Serial.available() > 1) {
    // read the incoming byte:
    incomingByte = Serial.parseInt();
  }
  return incomingByte;
}
