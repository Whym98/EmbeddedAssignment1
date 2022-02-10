const byte SigA = 18; //Pin Definitions
const byte SigB = 5;
const byte input1 = 19; 
const byte input2 = 21;
int input1state = 0; //Holds button state information
int input2state = 0;

void setup() //setup IO pins
{
  pinMode(SigA, OUTPUT);
  pinMode(SigB, OUTPUT);
  pinMode(input1, INPUT);
  pinMode(input2, INPUT);
}

void loop()
{
  int i = 0; //used in for loops
  int a = 300; //delay a
  int pulse = 0; //records the pulse length as it increases/decreases
  input2state = 0; //reset input2state
  input2state = digitalRead(input2); //check if button 2 is pressed (debounce not used as button condition is only checked once per loop)
  if(input2state == 0) //if button 2 is not pressed run loop, incrementing pulse length
  {
    for(i=0; i<=18; i++) //run all 18 pulses
    {
      pulse = a + (50*i); //Calculate pulse length starting at smallest pulse length
      digitalWrite(SigA, HIGH);
      delayMicroseconds(pulse); //pulse time for SigA
      digitalWrite(SigA, LOW);
      delayMicroseconds(100); //delay b
    }
    delayMicroseconds(10000);  //delay d
    digitalWrite(SigB, HIGH); //run SigB Pulse
    delayMicroseconds(50);
    digitalWrite(SigB, LOW);
  }
  else //if button 2 is pressed run loop, decrementing pulse length
  {
    pulse = 0; //reset pulse variable
    for(i=18; i>=0; i--) //run pulses starting with largest
    {
      pulse = a + (50*i); //Calculate pulse length starting with largest pulse length
      digitalWrite(SigA, HIGH);
      delayMicroseconds(pulse); //pulse time for SigA
      digitalWrite(SigA, LOW);
      delayMicroseconds(100); //delay b
    }
    delayMicroseconds(10000); //delay d
    digitalWrite(SigB, HIGH); //run SigB Pulse
    delayMicroseconds(50);
    digitalWrite(SigB, LOW);
  }
  input1state = digitalRead(input1); //check button 1
  while(input1state == 1) //while button 1 is pressed hold program here to prevent all output pulses
  {
    delayMicroseconds(1000); //debounce
    input1state = digitalRead(input1);//check button
  }
}
