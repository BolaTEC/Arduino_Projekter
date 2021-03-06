// DS1302_Serial_Easy 
// Copyright (C)2015 Rinky-Dink Electronics, Henning Karlsen. All right reserved
// web: http://www.RinkyDinkElectronics.com/
//
// A quick demo of how to use my DS1302-library to 
// quickly send time and date information over a serial link
//
// I assume you know how to connect the DS1302.
// DS1302:  CE pin    -> Arduino Digital 2
//          I/O pin   -> Arduino Digital 3
//          SCLK pin  -> Arduino Digital 4

#include <DS1302.h>

// Init the DS1302
DS1302 rtc(2, 3, 4);

void setup()
{
  // Set the clock to run-mode, and disable the write protection
  //rtc.halt(false);
  //rtc.writeProtect(false);
  
  // Setup Serial connection
  Serial.begin(9600);
  Serial.println("Ready");

  // The following lines can be commented out to use the values already stored in the DS1302
  rtc.setDOW(SUNDAY);        // Set Day-of-Week to FRIDAY
  rtc.setTime(12, 54, 0);     // Set the time to 12:00:00 (24hr format)
  rtc.setDate(9, 3, 2022);   // Set the date to August 6th, 2010 (dd/mm/yy)
}

void loop()
{
  // Send Day-of-Week
  Serial.print(rtc.getDOWStr());
  Serial.print(" ");
  
  // Send date
  Serial.print(rtc.getDateStr());
  Serial.print(" -- ");

  // Send time
  Serial.println(rtc.getTimeStr());
  
  // Wait one second before repeating :)
  delay (1000);
}
