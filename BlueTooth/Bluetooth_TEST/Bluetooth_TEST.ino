/*
 * Denne lille program gør at du kan forbinde med f.eks. PuTTY til din bluetooth forbindelse.
 * Husk at parre din computer med HC-05 først. Herefter vil den være på en COMPORT måske 5 eller 6
 * check selv efter i enhedshåndteringen
 * 
 * Du kan også hente Bluetooth Serial Terminal i Microsoft store, og kommunikere den vej igennem.
 * 
 * Når du skirver '1' uden apostroffer på terminalen, så vil LED på port 13 på Arduinoen tænde.
 * ligeledes hvis du skriver '0', så vil LED slukke.
 * 
 */
#include <SoftwareSerial.h>

#define KEY 2 // If it is input low level or connect to the air, the module is at paired or communication mode. If it’s input high level, the module will enter to AT mode.
#define VCC 3 // Power til HC-05 modulet
#define GND 4 // GND til HC-05 modulet
#define BT_RX 5 // Forbindes til TxD på Hc-05 board
#define BT_TX 6 // Forbindes til RxD på Hc-05 board
#define LED 7 // LED out on BTH module

SoftwareSerial mySerial(BT_RX, BT_TX);

void setup()
{
  pinMode(GND,OUTPUT);
  pinMode(VCC,OUTPUT);
  pinMode(KEY,OUTPUT);
  digitalWrite(KEY,LOW); // This needs to be LOW for module to be in Communication-mode
  delay(30);
  pinMode(LED,INPUT);
  // Power up module
  digitalWrite(GND,LOW);
  digitalWrite(VCC,HIGH);
  
 Serial.begin(9600);
 mySerial.begin(9600);
 pinMode(LED_BUILTIN, OUTPUT);
 Serial.write("Ready!\n");
}

void loop()
{
 if ( mySerial.available() )
 {
   char inBuf = mySerial.read();
   Serial.print( inBuf );
   switch (inBuf)
   {
    case '0':
      digitalWrite(LED_BUILTIN,LOW);
      break;
    case '1':
      digitalWrite(LED_BUILTIN,HIGH);
      break;
   }
 }
 if ( Serial.available() )
 {
   mySerial.print( Serial.read() );
 }
}
