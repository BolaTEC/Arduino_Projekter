/*
   Dette program tager mod kommandoer tal 0 til 255 for at styre en
   motors omdrejninger ved hjælp af PWM  0=STOP 128 = 50% power 255=100% power

   Programmet bruger INT0 på pin 2 (kan ikke ændres) og hver gang der kommer en 
   puls på dette ben vil en variabel blive talt op, og brugt i udregningen.
   I udregningen bliver tallet divideret med 4, og det er fordi der til dette
   forsøg, blev brugt en skive med 4 huller i.
*/

//***********************************
//Setup constants
//***********************************
const int pwm = 6;
const byte interruptPin = 2;

//***********************************
// Global variable
//***********************************
volatile float rev=0;
long rpm;
int oldtime=0;
int time;
int ledToggle = 0;
int motorSpeed = 0;
int oldSpeed = 0;

//***********************************
// Interrupt routine
// "isr" is my self chosen name
//***********************************
void isr() //interrupt service routine
{
  rev++;
}


void setup() {

    ///////////////////////////
    // FOR DEBUG PURPOSES
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, ledToggle);
    ///////////////////////////
    
    //***********************************
    // Set inout and output pins, set default value
    //***********************************
    pinMode(pwm,OUTPUT);
    analogWrite(pwm,0);
    pinMode(interruptPin, INPUT_PULLUP);
    
    //***********************************
    //Serial connection 9600 Baud
    //***********************************
    Serial.begin(115200);  // Initialize Serial connecion on Comport
    Serial.println("Ready!");
    
    //***********************************
    // Toogle the LED 13 for livelight
    //***********************************
    ledToggle=ledToggle + 1;
    digitalWrite(LED_BUILTIN,ledToggle%2 );
    
    //***********************************
    // Interrupt setup. USe LOW instead of RISING if problems.
    //***********************************
    attachInterrupt(digitalPinToInterrupt(interruptPin), isr, RISING);
}

void loop()
{
  delay(2000);
  detachInterrupt(digitalPinToInterrupt(interruptPin));           //detaches the interrupt
  time=millis()-oldtime;      //finds the time 
  oldtime=millis();           //saves the current time
  rpm=(rev/time)*60000/4;     //calculates rpm div by four due to 4 holes in plate going through sensor
  Serial.print(rev);          // measured value
  rev=0;
  Serial.print(" ");          // measured value
  Serial.print(time);         // measured value
  Serial.print(" ");          // measured value
  Serial.println(rpm);        // measured value
  MotorControl();
  attachInterrupt(digitalPinToInterrupt(interruptPin),isr,RISING);// activate interrupt again
}

void MotorControl()
{
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
      Serial.print("Motor speed set to: ");
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
