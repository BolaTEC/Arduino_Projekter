/**********************************************************/
/* This code takers a integer command between 0 and 180 
 * and command a servo to that angle 
 */
 
#include <Servo.h>

Servo myservo;  // create servo object to control a servo
int angle = 0;
int incomingByte = 0;// for incoming serial data
int oldAngle = 0;
const int servoPin = 9; // Change this number if you servo is attatched elsewhere.

void setup() {
    myservo.attach(servoPin);
    //myservo.attach(servoPin,1000,2000); // <-- Use this instead of the line above. Keeeps the servo from spinning around, this is minumum=1ms and maximum=2ms. Change this if your servo is acting strange (noisy) or does not turn enough.
    myservo.write(0);  // Reset angle

    //***********************************
    //Serial connection 9600 Baud
    //***********************************
    Serial.begin(9600);
    Serial.println("Ready");
    Serial.println("Input angle between 0 and 180 deg.");
}

void loop() {
  angle = readSerial();
 
  if ((oldAngle != angle) && ((angle >= 0) && (angle <= 180)))
  {
   Serial.print("Angle: ");
   Serial.println(angle);
   delay(200);
   myservo.write(angle);
   oldAngle=angle;
  }
  delay(500);
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
