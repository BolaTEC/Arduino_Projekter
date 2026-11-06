
#include <SoftwareSerial.h>

#define BT_TX 4 // Forbindes til RxD på Hc-05 board
#define BT_RX 7 // Forbindes til TxD på Hc-05 board

SoftwareSerial mySerial(BT_RX, BT_TX);

bool transmit = false;
float sensor = 0.0f;

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
   Serial.write( inBuf );
   switch (inBuf)
   {
    case '0':
      digitalWrite(13,LOW);
      transmit=false;
      break;
    case '1':
      digitalWrite(13,HIGH);
      transmit=true;
      break;
   }
 }
 if (transmit)
 {
  sensor= analogRead(A0);
   mySerial.print("Data: ");
   mySerial.println(sensor);
  //mySerial.print("\r\n");
 }
 delay(100);
}
