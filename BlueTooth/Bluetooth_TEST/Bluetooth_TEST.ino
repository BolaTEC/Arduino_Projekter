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

#define BT_TX 4 // Forbindes til RxD på Hc-05 board
#define BT_RX 7 // Forbindes til TxD på Hc-05 board

SoftwareSerial mySerial(BT_RX, BT_TX);

void setup()
{
 Serial.begin(9600);
 mySerial.begin(9600);
 pinMode(13, OUTPUT);
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
      digitalWrite(13,LOW);
      break;
    case '1':
      digitalWrite(13,HIGH);
      break;
   }
 }
 if ( Serial.available() )
 {
   mySerial.print( Serial.read() );
 }
}
