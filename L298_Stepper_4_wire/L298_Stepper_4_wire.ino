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
int in1 = 2;    
int in2 = 3;    
int in3 = 4;    
int in4 = 5;    

int delaytime = 2000; // Delay in Microseconds

int stepfw[4][4] = { {1,0,1,0} , {0,1,1,0} ,{0,1,0,1}, {1,0,0,1} };    //Step clockwise
int stepbw[4][4] = { {1,0,0,1} , {0,1,0,1}, {0,1,1,0}, {1,0,1,0}  };   //Step anti clockwise 

/***************************************/
// SETUP
/***************************************/
void setup()                    
{
  pinMode(in1, OUTPUT);    
  pinMode(in2, OUTPUT);    
  pinMode(in3, OUTPUT);        
  pinMode(in4, OUTPUT);     
 
  digitalWrite(in1, LOW); // Must be HIGH to avoid current consumption in idle state
  digitalWrite(in2, LOW);     
  digitalWrite(in3, LOW);   
  digitalWrite(in4, LOW);     
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
  digitalWrite(in1, LOW);   
  digitalWrite(in2, LOW);     
  digitalWrite(in3, LOW);   
  digitalWrite(in4, LOW);  
 }
 else if (tal>0)
 {
    Serial.println(tal);
    if (tal<10000)
    {
      for(int n=0; n <tal; n++) 
        doStep(stepfw);
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
     doStep(stepbw); 
 }  
}

/***************************************/
// DOSTEP
/***************************************/
void doStep(int steps[4][4]){
 for (int n=0 ; n < 4; n++){
   digitalWrite(in1, steps[n][0]);  
   digitalWrite(in2, steps[n][1]);  
   digitalWrite(in3, steps[n][2]);  
   digitalWrite(in4, steps[n][3]);  
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
