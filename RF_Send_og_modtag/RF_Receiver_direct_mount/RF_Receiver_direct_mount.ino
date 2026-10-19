//This code was written using the functions of the Virtual Wire Library.
//Function list here: http://www.airspayce.com/mikem/arduino/VirtualWire/VirtualWire_8h.html

// The receiver can be powered directly from +5V and GND if wanted. As can the CS pin be set to +5V. This
// way you can free 4 pins on the Arduino

#include <VirtualWire.h>

#define VCC 5 // Power til RF receiver modulet
#define GND 2 // GND til RF receiver modulet
//#define GND2 2 // GND til RF receiver modulet
//#define CS 10 // Linear Output/Test
#define RX_PIN 3 // ATAD på RF receiver modulet


void setup()
{
  pinMode(GND,OUTPUT);        // Can be omitted if powered directly
 // pinMode(GND2,OUTPUT);       // Can be omitted if powered directly
  //pinMode(CS,OUTPUT);         // Can be omitted if powered directly
  pinMode(VCC,OUTPUT);        // Can be omitted if powered directly
  delay(30);                  // Can be omitted if powered directly
  pinMode(LED_BUILTIN,OUTPUT);
  digitalWrite(LED_BUILTIN,LOW);

  // Power up module
  digitalWrite(GND,LOW);        // Can be omitted if powered directly
  //digitalWrite(GND2,LOW);       // Can be omitted if powered directly
  //digitalWrite(CS,HIGH);        // Can be omitted if powered directly
  digitalWrite(VCC,HIGH);       // Can be omitted if powered directly

  delay(200);

  vw_set_ptt_inverted(true); // On a communication line means that each 
    // party is either transmitting or receiving ( like a walkie talkie)
  vw_set_rx_pin(RX_PIN); // set receiver pin
  vw_setup(4000);        // Bits per sec
  vw_rx_start();         // Start Phase Locked Loop (listening to the receiver)
  Serial.begin(9600);
  Serial.write("Ready!\n");
}


void loop()
{
  uint8_t buf[VW_MAX_MESSAGE_LEN]; // 80 bytes is message length
  uint8_t buflen = VW_MAX_MESSAGE_LEN;

  if (vw_get_message(buf, &buflen)) { // if message received
    Serial.println("DATA received");
    // Terminate the sting at the right length.
    buf[buflen]='\0'; // NULL char at end of string


    if(buf[0]=='F'){  // and if the first letter in message array is D
      String str = (char*)buf;
      Serial.println(str);

      for(int i=0;i<5;i++){        // loop alternates between LED
          digitalWrite(LED_BUILTIN,HIGH);
          delay(100);
          digitalWrite(LED_BUILTIN,LOW);
          delay(100);
      }
    }  
  }
}
 
