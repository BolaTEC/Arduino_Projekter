/* Serial 7-Segment Display Example Code
    I2C Mode Stopwatch
   by: Jim Lindblom
     SparkFun Electronics
   date: November 27, 2012
   license: This code is public domain.
   
   This example code shows how you could use the Arduino Wire 
   library to interface with a Serial 7-Segment Display.
   
   There are example functions for setting the display's
   brightness, decimals, clearing the display, and sending a 
   series of bytes via I2C.
   
   Each I2C transfer begins with a Wire.beginTransmission(address)
   where address is the 7-bit address of the device set to 
   receive the data. Wire.write() sends a byte of data. I2C
   communication is closed with Wire.endTransmission().
   
   Circuit:
   Arduino -------------- Serial 7-Segment
     5V   --------------------  VCC
     GND  --------------------  GND
     SDA  --------------------  SDA (A4 on older 'duino's)
     SCL  --------------------  SCL (A5 on older 'duino's)


     PIN2 --------------------  Button connected to GND ! ! ! Must be this to use interupt 0 ! ! !
     PIN3 --------------------  Button to reset timer on any 
*/
#include <Wire.h> // Include the Arduino SPI library

// Here we'll define the I2C address of our S7S. By default it
//  should be 0x71. This can be changed, though.
const byte s7sAddress = 0x71;

bool timerRunning = false;   // True if timer is running
bool slowClock = false;      // The timer vil start (false) as sec:mili and when true min:sec
unsigned int counterL = 00;  // This variable will count milisec or sec
unsigned int counterH = 00;  // This variable will count sec or min
char tempString[10];  // Will be used with sprintf to create strings

const byte interruptPin2 = 2;  // To start/stop timer
const byte interruptPin3 = 3;  // To reset timer

/*************************************************************/
// ISR 2
void isr2() //interrupt service routine for pin 2
{
  if(timerRunning)
  {
    timerRunning=false;
  }
  else
  {
    timerRunning=true;
  }
}



/*************************************************************/
// SETUP
void setup()
{
  
  Wire.begin();  // Initialize hardware I2C pins
  
  setBrightnessI2C(128);  // Medium brightness      11mA
  
  // Clear the display before jumping into loop
  clearDisplayI2C();
  setDecimalsI2C(0b00010000);  // Sets clock colon on  10:00  
  pinMode(interruptPin2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin2), isr2, RISING);
  pinMode(interruptPin3, INPUT_PULLUP);
  //attachInterrupt(digitalPinToInterrupt(interruptPin3), isr3, RISING);
}

void loop()
{
  
  // Magical sprintf creates a string for us to send to the s7s.
  //  The %4d option creates a 4-digit integer.
  sprintf(tempString, "%4d", counterH*100+counterL);
  
  // This will output the tempString to the S7S
  s7sSendStringI2C(tempString);

  // Halt here if timer is stopped.
  while (!timerRunning)
  {
    if (digitalRead(interruptPin3)==LOW)
      reset();
    delay(10);
  }
  counterL++;  // Increment the counter
  if (slowClock==false)
  {
    if (counterL==100)
    {
      counterL=0;
      counterH++;
    }
    if (counterH == 60)
    {
      slowClock=true; // When 59:59 is reached then timer will shit to counting minutes and seconds.
      counterL = 0;
      counterH = 1;
  //    delay(100);  // This will make the display update at 1Hz.*/
    }
  //  else
  //  {
      delay(10);  // This will make the display update at .01Hz.*/  
  //  }
  }
  else
  {
    if (counterL==60)
    {
      counterL=0;
      counterH++;
    }
    // If timer is expired 59:59 min:sec
    if (counterH == 60)
    {
      while(1) // endless loop flashing "----"
      {
        s7sSendStringI2C("----");    
        delay(500);
        clearDisplayI2C();
        delay(500);
      }
    }
    delay(1000);  // This will make the display update at 1Hz.*/  
  }
}

// This custom function works somewhat like a serial.print.
//  You can send it an array of chars (string) and it'll print
//  the first 4 characters in the array.
void s7sSendStringI2C(String toSend)
{
  Wire.beginTransmission(s7sAddress);
  for (int i=0; i<4; i++)
  {
    Wire.write(toSend[i]);
  }
  Wire.endTransmission();
}

// Send the clear display command (0x76)
//  This will clear the display and reset the cursor
void clearDisplayI2C()
{
  Wire.beginTransmission(s7sAddress);
  Wire.write(0x76);  // Clear display command
  Wire.endTransmission();
}

// Set the displays brightness. Should receive byte with the value
//  to set the brightness to
//  dimmest------------->brightest
//     0--------127--------255
void setBrightnessI2C(byte value)
{
  Wire.beginTransmission(s7sAddress);
  Wire.write(0x7A);  // Set brightness command byte
  Wire.write(value);  // brightness data byte
  Wire.endTransmission();
}

// Turn on any, none, or all of the decimals.
//  The six lowest bits in the decimals parameter sets a decimal 
//  (or colon, or apostrophe) on or off. A 1 indicates on, 0 off.
//  [MSB] (X)(X)(Apos)(Colon)(Digit 4)(Digit 3)(Digit2)(Digit1)
void setDecimalsI2C(byte decimals)
{
  Wire.beginTransmission(s7sAddress);
  Wire.write(0x77);
  Wire.write(decimals);
  Wire.endTransmission();
}


/*************************************************************/
// Reset timer
void reset()
{
  // Only reset if timer is stopped.
  if (!timerRunning)
  {
    counterL=0;
    counterH=0;
    slowClock=false;
    sprintf(tempString, "%4d", counterH*100+counterL);
    // This will output the tempString to the S7S
    s7sSendStringI2C(tempString);
  }
}
