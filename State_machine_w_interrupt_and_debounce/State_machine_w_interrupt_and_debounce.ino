/***********************************************/
/* Interrupt controlled State machine code     */
/* This State machine is for use with buttons  */
/* that might have bounce jitter to be removed */
/***********************************************/

//#define DEBUG  //<-----   uncomment if you want more status writing on your serial connection

const int red = 5;
const int yel = 6;
const int gre = 7;
const int s1 = 2;               // sensor 1 (INT0)
const int s2 = 3;               // sensor 2 (INT1)
const int noOfStates = 3;       // Number of states in this statesmachine
const unsigned long debounceTime = 500;  // Debounce in millis. 

int state = 0;                  // The new state of the state machine
int old_state = 0;              // Stores old state, hence not writing to ports too often.
volatile int intCalled = 0;     // Keep track on which interrupt was called. volatile declared because the state variable is changed in a interrupt function.
unsigned long deltaTime = 0;    // Make sure do debounce the interrupt on s1 pin
unsigned long currentTime = 0;  // Make sure do debounce the interrupt on s2 pin
	
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
	pinMode(red, OUTPUT);
	pinMode(yel, OUTPUT);
	pinMode(gre, OUTPUT);
	digitalWrite(red,LOW);
	digitalWrite(yel,LOW);
	digitalWrite(gre,LOW);
	pinMode(s1, INPUT_PULLUP);
	pinMode(s2, INPUT_PULLUP);
	attachInterrupt(digitalPinToInterrupt(s1),isr1,LOW); // Trigger isr1 when pin connection s1 is LOW
	attachInterrupt(digitalPinToInterrupt(s2),isr2,LOW); // Trigger isr2 when pin connection s2 is LOW
}
	
/******************************/
/* interrupt service routines */
/******************************/
void isr1() 
{
	// Do not allow any other interrupts until debounce time is clear.
	detachInterrupt(digitalPinToInterrupt(s1));
	detachInterrupt(digitalPinToInterrupt(s2));
	// Only allow intCalled to change if interrupt debounce time is not in active periode.
	if (intCalled == 0)
	{
		intCalled = 1;
	}  
}

void isr2() 
{
	// Do not allow any other interrupts until debounce time is clear.
	detachInterrupt(digitalPinToInterrupt(s2));
	detachInterrupt(digitalPinToInterrupt(s1));
	// Only allow intCalled to change if interrupt debounce time is not in active periode.
	if (intCalled == 0)
	{
		intCalled = 2;
	}
}
	
/*****************************/
/* MAIN LOOP                 */
/*****************************/
void loop()
{
	// Only allow state to change if interrupt reoccurence are above debouncetime
	if (((millis() - deltaTime) > debounceTime)&&(intCalled == -1))
	{
		intCalled = 0;
		attachInterrupt(digitalPinToInterrupt(s1),isr1,LOW);
		attachInterrupt(digitalPinToInterrupt(s2),isr2,LOW);

		delay(1);
	}

	CheckInt1();
	CheckInt2();

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
	delay(100);
}


/******************************/
/* interrupt check routines */
/******************************/
void CheckInt1() 
{
	#ifdef DEBUG
	  Serial.print("CheckInt1, State :");
	  Serial.print(intCalled);
	  Serial.print(", ");
	  Serial.println(state);
	#endif
	// Only if interrupt 0 (s1) did trigger
	if (intCalled==1)
	{
	  if (state < noOfStates) // Only increment if state is not last state=3;
		state = state + 1;
	  else
		state = 0;
	  
	  deltaTime = millis();  // Reset debounce timer
	  intCalled = -1;

	}
}

void CheckInt2() 
{
	#ifdef DEBUG
	  Serial.print("CheckInt2, State :");
	  Serial.print(intCalled);
	  Serial.print(", ");
	  Serial.println(state);
	#endif
	// Only if interrupt 1 (s2) did trigger
	if (intCalled==2)
	{
	  if (state > 0)          // Only decrement if state is not last state=0;
		state = state - 1;
	  else
		state = noOfStates;

	  deltaTime = millis();  // Reset debounce timer
	  intCalled = -1;
	}
}
