/* This code reads a integer 2..13 from the serial port.
 *  Then Toggles the output. All ports start as LOW
 *  
 *  So, if you write 13, the port 13 will be set to HIGH the first time, and LOW the next.
 *  A serial message will write to the console, what pin it high or low.
 */


#include <wiring_private.h>
#include <pins_arduino.h>


void setup() {
  // initialize both serial ports:
  Serial.begin(9600);
  while (!Serial);
  Serial.println("\nReady");
  
  for (int i=2; i <= 13; i++){
      pinMode(i,OUTPUT);
      digitalWrite(i,LOW);
  }
}

void loop() {
  int readVal = ReadSerial();
  if ((readVal >= 2)&&(readVal<=13)){
    if (digitalReadOutputPin(readVal)==LOW)
    {
      digitalWrite(readVal,HIGH);
      Serial.print("Port : ");
      Serial.print(readVal);
      Serial.println(" set to : HIGH");
    }
    else{
      digitalWrite(readVal,LOW); 
      Serial.print("Port : ");
      Serial.print(readVal);
      Serial.println(" set to : LOW");
    }
  }
}


int digitalReadOutputPin(uint8_t pin)
{
  uint8_t bit = digitalPinToBitMask(pin);
  uint8_t port = digitalPinToPort(pin);
  if (port == NOT_A_PIN) 
    return LOW;

  return (*portOutputRegister(port) & bit) ? HIGH : LOW;
}

/*****************************************/
// READ SERIAL
/*****************************************/
int ReadSerial(){
  int inByte = -99;
  if (Serial.available() > 1) {
    // read the incoming byte:
    inByte = Serial.parseInt();
  }
  return inByte;
}
