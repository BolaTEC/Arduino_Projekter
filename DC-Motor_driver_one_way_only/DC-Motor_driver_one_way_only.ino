/*
   Dette program tager mod kommandoer tal 0 til 255 for at styre en DC-motor
   0=STOP f.eks. 128=50% 255=100% power
*/

//***********************************
//Setup constants
//***********************************
const int m1 = 6;    

//***********************************
// Global variable
//***********************************
int incomingByte = -9999;
int power = -9999;
int oldpower = -9999;

//**********************************
// SETUP
//**********************************
void setup()                    
{
  pinMode(m1, OUTPUT);    
 
  analogWrite(m1, 0);   
  Serial.begin(9600);  
  Serial.println("Ready\n\n");
  Serial.println("Give motor PWM-command e.g. ");
  Serial.println("(128 for 50% power or 255 for 100% power 0= stop)");
}

//**********************************
// LOOP
//**********************************
void loop()                     
{
 power = readSerial();
  if (power!= oldpower){
    Serial.println(power);
 	analogWrite(m1,power);
    oldpower = power;
  }
  delay(100);
}

//***********************************
// Read data from UART connection
//***********************************
int readSerial() {
  if (Serial.available() > 1) {
    // read the incoming byte:
    incomingByte = Serial.parseInt();
  }
  return incomingByte;
}
