#define SERVO 9
int rotations = 0;
int old_rotations = 0;
int pulseWidth = 2000;
int incomingByte=0;

/***************************************/
// SETUP
/***************************************/
void setup() {
    pinMode(SERVO,OUTPUT);
    digitalWrite(SERVO,LOW);
    //***********************************
    //Serial connection 9600 Baud
    //***********************************
    Serial.begin(9600);
    Serial.println("Ready");
    Serial.println("Give servo number of pulses e.g. ");
    Serial.println("100 for 100 pulses)");
    Serial.println("To ajust pulsewidth which determine the direction of rotation");
    Serial.println("set 11000[ms] for fast CCW or 12000[ms] for fast CW");
    Serial.println("The extra 10000 will be subtracted from the time, so time is 1000 [ms]");
    Serial.println("if you withe 11000 - DO NOT USE SAME NUMBER TWICE");

}

/***************************************/
// LOOP
/***************************************/
void loop() {
  // put your main code here, to run repeatedly:

  rotations = readSerial();

  // If user set number >10000 then time needs adjustment.
  if (rotations >10000)
  {
    pulseWidth= rotations - 10000; // Subtract 10000 to get the real new pulsewidth
    Serial.print("Time :");
    Serial.println(pulseWidth);
    old_rotations = rotations;
  }
  else if (rotations != old_rotations)
  {
    Serial.println(rotations);
    for(int i=0;i<rotations;i=i+1)
    {
      digitalWrite(SERVO,HIGH);
      delayMicroseconds(pulseWidth);
      digitalWrite(SERVO,LOW);
      delayMicroseconds(20000-pulseWidth);
    }
    old_rotations = rotations;
  }
}

//***********************************
// Read data from UART connection
//***********************************
int readSerial() {

  if (Serial.available() > 0) {
    // read the incoming byte:
    incomingByte = Serial.parseInt();
  }
  return incomingByte;
}
