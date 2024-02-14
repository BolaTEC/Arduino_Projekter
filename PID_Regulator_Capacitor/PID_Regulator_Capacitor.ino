//***********************************
// Compiler parameters
//***********************************
#define _IFDEBUG_ false
#define _GRAPH_OF_PF_ false
//***********************************
// Constant variable
//***********************************

 const int sensorPin = A0;
 const int pwmPin = 9;

 
//***********************************
// Global variable
//***********************************

float dataRead = 0.0;   // for incoming serial data

unsigned long time;
unsigned long measureTime;

int sensorVal=0;
float setpoint = 0;
int pwmInterval = 0;
float outPID=0.0;

float process_feedback=0.0;
float previous_error = 0.0;

float Kp = 1.0;
float Ki = 1.0;
float Kd = 0.5;

float integral=0.0;
int dt=100; // dt

 //******************************************************
 // SETUP FUNCTION
 //******************************************************
 void setup()
 {
    Serial.begin(115200); //Open a serial port
    pinMode(pwmPin,OUTPUT);
    analogWrite(pwmPin,pwmInterval);
    Serial.println("Ready!");
    Serial.println("Enter output voltage setpoint");
 }

 //******************************************************
 // LOOP FUNCTION
 //******************************************************
 void loop()
 {
     dataRead = readSerial(setpoint);
     if ((0.0 < dataRead < 5.0)&&(setpoint!=dataRead))
     {
      // Reset all variubles
      Serial.println(dataRead);
      setpoint = dataRead;
      outPID=0.0;
      integral=0.0;
      previous_error=0.0;
      time=micros();
     }

     // Read raw process_feedback
     sensorVal=analogRead(sensorPin);
     // note the time
     measureTime =  micros() - time; // Time form setpoint was set;
     process_feedback = (sensorVal/1024.0) *5.0;
     PID(process_feedback,previous_error,outPID);

     int DACout = outPID*1024/5;
     pwmInterval = map(DACout,0,1023,0,255);

     // Make sure DAC value is not out of bound
     if (pwmInterval>255)
        pwmInterval=255;
     if (pwmInterval<0)
        pwmInterval=0;

     analogWrite(pwmPin,pwmInterval);
#if (!_GRAPH_OF_PF_)
     Serial.print("; Time: ");
     Serial.print(measureTime);
     Serial.print("; Pf: ");
#endif
     Serial.print(process_feedback);  // <-- Print only this when _GRAPH_OF_PF_ is defined
#if (!_GRAPH_OF_PF_)
     Serial.print("; Out: ");
     Serial.print(outPID);
     Serial.print("; PWM: ");
     Serial.println(pwmInterval);
#else
      Serial.println();
#endif  
    
     delay(dt);
   
 }

 //******************************************************
 // PID FUNCTION
 //******************************************************
 void PID(float pf, float &prev_err, float &out)
 {
  float error = setpoint - pf;
  integral = integral + (error*(dt/1000.0));
  float derivative = (error - prev_err)/((float)dt/1000.0);
  float output = (Kp*error) + (Ki*integral) + (Kd*derivative);
  
#if (_IFDEBUG_)
      Serial.print("PrevE: ");
      Serial.print(prev_err);
      Serial.print("; E: ");
      Serial.print(error);
      Serial.print("; I: ");
      Serial.print(integral);
      Serial.print("; D: ");
      Serial.print(derivative);
#endif
      prev_err = error;
      out=output;
 }

//***********************************
// Read data from UART connection
//***********************************
float readSerial(float ind) {
  float incomingFloat = ind;
  while (Serial.available() > 1) {   // <--- Some PCs will work with >0 others >1
    delay(1);

    // read the incoming float:
    incomingFloat = Serial.parseFloat();
    serialFlush();
  }

  return incomingFloat;
}

//*******************************************
// Flushes the serial buffer for extra chars
//*******************************************
void serialFlush(){
  if(Serial.available() > 0) {
    char t = Serial.read();
  }
} 
