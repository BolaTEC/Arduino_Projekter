/*
 * Use this code to talk to HC-05 modules.
 * To set module in AT command mode, make sure you
 * power on while having KEY/EN HIGH.
 * If this does not work, try holding the pushbutton in
 * on the HC-05 bord while while connecting the KEY/EN pin 
 * to VCC (Especialy a ZS-040 BOARD)
 * 
 *  Set the serial monitor to "38400 Baud", and "Both NL & CR"
 * 
 * AT commands:
 * Command      Answer
 * AT           OK 
 * AT+VERSION?  VERSION:3.0-20170601
 * AT+CLASS?    +CLASS:1  // or 0 should be 1 for phones to connect.
 * AT+UART?     +UART:9600,0,0  // Or could be 38400,0,0 set with AT+UART:9600,0,0
 * 
 * More commands here : https://www.engineersgarage.com/sites/default/files/newinline/Table-Listing-AT-Commands-HC-05-Bluetooth-Module.%20Jpg
 * 
 */
#define KEY 2 // If it is input low level or connect to the air, the module is at paired or communication mode. If it’s input high level, the module will enter to AT mode.
#define VCC 3 // Power til HC-05 modulet
#define GND 4 // GND til HC-05 modulet
#define BT_RX 5 // Forbindes til TxD på Hc-05 board
#define BT_TX 6 // Forbindes til RxD på Hc-05 board
#define LED 7 // LED out on BTH module


#include <SoftwareSerial.h>
SoftwareSerial mySerial(BT_RX, BT_TX);

void setup() {
  pinMode(GND,OUTPUT);
  pinMode(VCC,OUTPUT);
  pinMode(KEY,OUTPUT);
  digitalWrite(KEY,HIGH); // This needs to be high for module to be in AT-mode
  delay(30);
  pinMode(LED,INPUT);
  // Power up module
  digitalWrite(GND,LOW);
  digitalWrite(VCC,HIGH);
  
  Serial.begin(9600);  // Arduino default speed, can be set to match HC-05 at 38400 
  delay(1000);
  mySerial.begin(38400); // This is default speed used by the HC-05 while in AT command mode.  
  delay(1000);
  Serial.println("Enter AT commands:");
}

/******************************************/
// SETUP
/******************************************/
void loop()
{

if (mySerial.available())
  Serial.write(mySerial.read());

if (Serial.available())
  mySerial.write(Serial.read());

}
