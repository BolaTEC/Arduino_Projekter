/**********************************************/
/* Interrupt controlled State machine code    */
/* This State machine is only to be used      */
/* with an clear signal with no bounce jitter */
/**********************************************/

const int red = 5;
const int yel = 6;
const int gre = 7;
const int s1 = 2;  // sensor 1 (INT0)
const int s2 = 3;  // sensor 2 (INT1)

volatile int state = 0;       // volatile declared because the state variable is changed in a interrupt function.
int old_state = 0;            // Stores old state, hence not writing to ports too often.

bool toggle = false;          // To make the build in LED toggle light

/*****************************/
/* MAIN SETUP                */
/*****************************/
void setup()
{
  //-----------------------------------------------------
  // Not needed int standalone Arduino embedded system.
  Serial.begin(9600);  
  Serial.println("Ready");
  //-----------------------------------------------------
  pinMode(LED_BUILTIN , OUTPUT);

  pinMode(red, OUTPUT);
  pinMode(yel, OUTPUT);
  pinMode(gre, OUTPUT);
  digitalWrite(red,LOW);
  digitalWrite(yel,LOW);
  digitalWrite(gre,LOW);
  pinMode(s1, INPUT_PULLUP);
  pinMode(s2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(s1),isr1,FALLING);
  attachInterrupt(digitalPinToInterrupt(s2),isr2,FALLING);
}

/******************************/
/* interrupt service routines */
/******************************/
void isr1() 
{
  if (state < 3)// Only increment if state is not last state=3;
    state = state + 1;
  else
    state = 0;
}

void isr2() 
{
    if (state > 0)// Only decrement if state is not last state=0;
      state = state - 1;
    else
      state = 3;   
}

/*****************************/
/* MAIN LOOP                 */
/*****************************/
void loop()
{
  if (state != old_state)
  {
  switch(state){
    case 1:
      digitalWrite(red,LOW);
      digitalWrite(yel,LOW);
      digitalWrite(gre,HIGH);
      //-----------------------------------------------------
      // Not needed int standalone Arduino embedded system.
      Serial.println("STATE 1");
      //-----------------------------------------------------
      break;
    case 2:
      digitalWrite(red,LOW);
      digitalWrite(yel,HIGH);
      digitalWrite(gre,LOW);
      //-----------------------------------------------------
      // Not needed int standalone Arduino embedded system.
      Serial.println("STATE 2");
      //-----------------------------------------------------
      break;
    case 3:
      digitalWrite(red,HIGH);
      digitalWrite(yel,LOW);
      digitalWrite(gre,LOW);
      //-----------------------------------------------------
      // Not needed int standalone Arduino embedded system.
      Serial.println("STATE 3");
      //-----------------------------------------------------
      break;
    default:
      digitalWrite(red,LOW);
      digitalWrite(yel,LOW);
      digitalWrite(gre,LOW);
      //-----------------------------------------------------
      // Not needed int standalone Arduino embedded system.
      Serial.println("IDLE STATE 0");
      //-----------------------------------------------------
      break;
    }
    old_state = state;
  }
  delay(200);
  toggle=!toggle;                       // Toggle the variable 
  digitalWrite(LED_BUILTIN ,toggle);    // Update the build in LED status 
}
