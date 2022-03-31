int in1 = 2;    
int in2 = 3;    
int in3 = 4;    
int in4 = 5;    

int delaytime = 2 ;

int stepfw[4][4] = { {1,0,0,1} , {0,1,0,1} ,{0,1,1,0}, {1,0,1,0} };    //Step clockwise
int stepbw[4][4] = { {1,0,1,0} , {0,1,1,0}, {0,1,0,1}, {1,0,0,1}  };   //Step anti clockwise 

/***************************************/
// SETUP
/***************************************/
void setup()                    
{
  pinMode(in1, OUTPUT);    
  pinMode(in2, OUTPUT);    
  pinMode(in3, OUTPUT);        
  pinMode(in4, OUTPUT);     
 
  digitalWrite(in1, LOW);   
  digitalWrite(in2, LOW);     
  digitalWrite(in3, LOW);   
  digitalWrite(in4, LOW);     
  Serial.begin(9600); 
  Serial.println("Ready\n\n");
  Serial.println("Give stepper order e.g. ");
  Serial.println("(-100 for CCW 100 steps or 100 for CW 100 steps 0= stop)");
}
/***************************************/
// LOOP
/***************************************/
void loop()                     
{
 int tal = readSerial();
 if (tal>0)
 {
   Serial.println(tal);

   for(int n=0; n <tal; n++) 
     doStep(stepfw); 
 }  
 if ((tal<0)&&(tal!=-9999))
 {
   Serial.println(tal);

   for(int n=0; n <tal*-1; n++) 
     doStep(stepfw); 
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
   delay(delaytime);  
 }
}
//***********************************
// Read data from UART connection
//***********************************
int readSerial() {
  int incomingByte = -9999;
  while (Serial.available() > 0) {
    // read the incoming byte:
    incomingByte = Serial.parseInt();
  }
  return incomingByte;
}
