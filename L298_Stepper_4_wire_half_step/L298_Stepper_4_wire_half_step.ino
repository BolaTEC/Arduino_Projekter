// Stepper Code for L298 board
//
// Stepper with 4 wires this tried with 17HS19-2004S1
//
// Wire colors
// Black Phase A   = OUT1
// Green Phase ~A  = OUT2
// Red   Phase B   = OUT3
// Blue  Phase ~B  = OUT4
//
// Change delaytime variable to slow of speed up stepper movement
// 
// Connect from L298 board to Arduino pins like this:
// in1 = pin 8;    
// in2 = pin 9;    
// in3 = pin 10;    
// in4 = pin 11;    

int delaytime = 2000; // Delay in Microseconds

byte stepfw[8] = {0x0A,0x02,0x06,0x04,0x05,0x01,0x09,0x08};
byte stepbw[8] = {0x08,0x09,0x01,0x05,0x04,0x06,0x02,0x0A};

/***************************************/
// SETUP
/***************************************/
void setup()                    
{
  DDRB=0xff;     // Set D8-D13 to OUTPUT
  PORTB = 0xf0;  // Set D8-D11 to LOW and D12-D13 to HIGH
    
  Serial.begin(9600); 
  Serial.println("Ready\n\n");
  Serial.println("Give stepper order e.g. ");
  Serial.println("(-100 for CCW 100 steps or 100 for CW 100 steps 0= stop)");
  Serial.println("\n(>10000 for change delaytime (speed) e.g. 10500 gives 1500 ms delay)");
    Serial.println("(10000 < delay < 32765)");

  
}
/***************************************/
// LOOP
/***************************************/
void loop()                     
{
 int tal = readSerial();
 if (tal==0)
 {
  Serial.println(tal);
  PORTB = 0xf0;
 }
 else if (tal>0)
 {
    Serial.println(tal);
    if (tal<10000)
    {
      for(int n=0; n <tal; n++) 
        doStep(stepfw,sizeof(stepfw));
    }
    else
    {
      delaytime = tal-9000;
      Serial.print("delay= ");
      Serial.println(delaytime,DEC);
    } 
 }  
 else if ((tal<0)&&(tal!=-9999))
 {
   Serial.println(tal);

   for(int n=0; n <tal*-1; n++) 
     doStep(stepbw,sizeof(stepbw)); 
 }  
}

/***************************************/
// DOSTEP
/***************************************/
void doStep(byte steps[],int size){
 for (int n=0 ; n < size; n++){
  PORTB = steps[n];
  delayMicroseconds(delaytime);  
 }
}
//***********************************
// Read data from UART connection
//***********************************
int readSerial() {
  int incomingByte = -9999;
  if (Serial.available() > 0) {
    // read the incoming byte:
    incomingByte = Serial.parseInt();
  }
  return incomingByte;
}
