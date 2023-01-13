// Define Trig and Echo pin:
#define trigPin 7
#define echoPin 8

// Give the motor control pins names:
#define pwmA 3
#define pwmB 11
#define dirA 12
#define dirB 13

// Buzzer pins
#define buzzerVCC 6
#define buzzerIO 5
#define buzzerGND 4

void setup() {
  // Define inputs and outputs:
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  // Set the PWM and brake pins so that the direction pins can be used to control the motor:
  pinMode(dirA, OUTPUT);
  pinMode(dirB, OUTPUT);
  pinMode(pwmA, OUTPUT);
  pinMode(pwmB, OUTPUT);
  pinMode(buzzerVCC, OUTPUT); //Set buzzerPin as output
  pinMode(buzzerIO, OUTPUT); //Set buzzerPin as output
  pinMode(buzzerGND, OUTPUT); //Set buzzerPin as output

  digitalWrite(dirA, LOW);
  digitalWrite(dirB, LOW);
  digitalWrite(pwmA, LOW);
  digitalWrite(pwmB, LOW);
  digitalWrite(buzzerVCC, HIGH);
  digitalWrite(buzzerIO, HIGH);
  digitalWrite(buzzerGND, LOW);


  //***********************************
  //Serial connection 9600 Baud
  //***********************************
  Serial.begin(9600);

}

void loop() {
  int afstand= pingSonar();
  if (afstand < 8)
  {
  beep(100);
  delay(1000);
  //CW
  digitalWrite(dirA,LOW);
  digitalWrite(pwmA,HIGH);
  digitalWrite(dirB,HIGH);
  digitalWrite(pwmB,HIGH);
  delay(1000);
  // STOP
  digitalWrite(pwmA,LOW);
  digitalWrite(pwmB,LOW);
  delay(1000);
  //CCW
  digitalWrite(dirA,HIGH);
  digitalWrite(pwmA,HIGH);
  digitalWrite(dirB,LOW);
  digitalWrite(pwmB,HIGH);
  delay(1000);
  // STOP
  digitalWrite(pwmA,LOW);
  digitalWrite(pwmB,LOW);
  delay(2000);
  }
}

void beep(unsigned int delayms) { //creating function
  analogWrite(buzzerIO, 20); //Setting pin to high
  delay(delayms); //Delaying
  digitalWrite(buzzerIO ,HIGH); //Setting pin to LOW
}

int pingSonar()
{
  long duration=0;
  int distance=0.0;
    // Clear the trigPin by setting it LOW:
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);

  // Trigger the sensor by setting the trigPin high for 10 microseconds:
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the echoPin, pulseIn() returns the duration (length of the pulse) in microseconds:
  duration = pulseIn(echoPin, HIGH);
  // Calculate the distance:
  distance = duration * 0.034 / 2;
  return distance;
}
