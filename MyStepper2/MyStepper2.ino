/***************************
This code is shared by elecrow.com
it is public domain, enjoy!
it is used to control 28BYJ stepper
it can be changed to control almost all the 4-wire or 5-wire stepper.
*************************/

/*
The time Series to control the stepper
--make your making more easy!
*/
byte CCW[8] = {0x09,0x01,0x03,0x02,0x06,0x04,0x0c,0x08};
byte CW[8] = {0x08,0x0c,0x04,0x06,0x02,0x03,0x01,0x09}; 

/*byte CCW[4] = {0x06,0x05,0x09,0x0A};
byte CW[4] = {0x0A,0x09,0x05,0x06}; */
const int noOfStepPatterns = sizeof(CW);

int oldSteps =0;
int steps=0;
int incomingByte = 0;   // for incoming serial data
int tidsDelay = 1150; 


void Motor_CCW(int steps)    //the steper move 360/64 angle at CouterClockwise 
{
  for(int k=0;k < steps;k++)
    for(int i=0;i < noOfStepPatterns;i++)
        for(int j = 0; j < noOfStepPatterns; j++)
        {
          PORTB = CCW[j];
          if (tidsDelay>9999)
            delay(tidsDelay/10);
          else
            delayMicroseconds(tidsDelay);
        }
}

void Motor_CW(int steps)  //the steper move 360/64 angle at Clockwise
{
  steps = steps * -1; // Remove sign
  for(int k=0;k < steps;k++)
    for(int i = 0; i < noOfStepPatterns; i++)
      for(int j = 0; j < noOfStepPatterns; j++)
      {
        PORTB = CW[j];
        if (tidsDelay>9999)
            delay(tidsDelay/10);
          else
            delayMicroseconds(tidsDelay);      }
}


void setup()
{

  //***********************************
  //Serial connection 9600 Baud
  //***********************************
  Serial.begin(9600);
  
  Serial.println("Enter speed clockwise from 1 to 299 and counter clockwise -1 to -299, enter 0 to stop.");
  DDRB=0xff;     // Set D8-D13 to OUTPUT
  PORTB = 0xf0;  // Set D8-D11 to LOW and D12-D13 to HIGH
  Serial.print("\nNumber of Step Patterns: ");
  Serial.println(noOfStepPatterns);
  Serial.println("Ready!");
  
  
}

void loop()
{
  steps = readSerial();
  
  if (steps!=oldSteps)
  {
    Serial.println(steps);
  
    if(steps==0)
    {
      PORTB =0xf0;
    }
    if(steps<0)
    {
      Motor_CW(steps);  //make the stepper to clockwise rotate
    }
    if(steps>0)
    {
      if (steps > 300)
        tidsDelay = steps;
      else
        Motor_CCW(steps);  //make the stepper to counterclockwise rotate
    }
    oldSteps=steps;
  }
delay(1000);
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
