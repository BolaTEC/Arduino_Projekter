int in1 = 2;    
int in2 = 3;    
int in3 = 4;    
int in4 = 5;    

int delaytime = 2 ;

int stepfw[4][4] = { {1,0,0,1} , {0,1,0,1} ,{0,1,1,0}, {1,0,1,0} };    //Step clockwise
int stepbw[4][4] = { {1,0,1,0} , {0,1,1,0}, {0,1,0,1}, {1,0,0,1}  };   //Step anti clockwise 



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
}


void doStep(int steps[4][4]){

 for (int n=0 ; n < 4; n++){
   digitalWrite(in1, steps[n][0]);  
   digitalWrite(in2, steps[n][1]);  
   digitalWrite(in3, steps[n][2]);  
   digitalWrite(in4, steps[n][3]);  
   delay(delaytime);  
 }
  
  
}


void loop()                     
{
 
 for(int n=0; n <50; n++) 
   doStep(stepfw); 

 for(int n=0; n <50; n++) 
   doStep(stepbw); 
  
  
  
}
