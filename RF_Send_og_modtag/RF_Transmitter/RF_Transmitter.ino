//
//This code was written using the functions of the Virtual Wire Library.
//Function list here: http://www.airspayce.com/mikem/arduino/VirtualWire/VirtualWire_8h.html
//
// In this example the VCC and GND needs to be wired to the Arduino +5 and GND on the board
// otherwise the module is not getting enough power.
//
#include <VirtualWire.h>
const char* message = "Det virker!!!\0";

#define TX_PIN 12 // DATA på RF transmitter modulet
#define BUTTON 2 // Transmit trigger pin

void setup() {

  pinMode(TX_PIN,OUTPUT);
  digitalWrite(TX_PIN,LOW); 
  delay(30);
  pinMode(LED_BUILTIN,OUTPUT);
  digitalWrite(LED_BUILTIN,LOW);

  // put your setup code here, to run once:
  pinMode(BUTTON,INPUT_PULLUP);
  vw_set_ptt_inverted(true); //On a communication line means that each
  // party is either transmitting or receiving (Like Walkie-Talkie)
  vw_set_tx_pin(TX_PIN);
  vw_setup(4000);
}

void loop() {
  //if (digitalRead(BUTTON)==LOW) // uncomment this line, if you only want the module to transmit, when BUTTON pin is LOW.
  {
    digitalWrite(LED_BUILTIN,HIGH);
    //message="X";
    vw_send((uint8_t *)message,strlen(message)); //send the message
    vw_wait_tx(); //Wait until the whole message is gone
   // delay(1);
    digitalWrite(LED_BUILTIN,LOW);
  }
  delay(1000); //debug purposes // comment this line out if you uncomment the line above.
}
