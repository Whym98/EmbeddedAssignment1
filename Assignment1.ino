const byte SigA = 18;
const byte SigB = 5;
const byte input1 = 19;
const byte input2 = 21;
int input1state = 0;
int input2state = 0;
int SigBstate = 0;
int SigAstate = 0;
void setup()
{
  Serial.begin(115200);
  pinMode(SigA, OUTPUT);
  pinMode(SigB, OUTPUT);
  pinMode(input1, INPUT);
  pinMode(input2, INPUT);
  ledcAttachPin(SigB, 0); //pin5 clock 0
  ledcSetup(0, 20000, 8); //clock 0, freq 20KHz, Resolution 8 bit
}

void loop()
{
  while(SigBstate==0)
  {
    //hold to prevent unalignment with SigB
    SigBstate == bitRead(GPIO_OUT_REG, SigB);
  }
  SigBstate = 0;
  ledcWrite(0, 4); //set clock0 to 0 dutycycle
  int i = 0;
  int a = 300;
  int pulse = 0;
  for(i=0; i<=18; i++) //run all 18 pulses
  {
    pulse = a + (50*i);
    digitalWrite(SigA, HIGH);
    SigAstate = bitRead(GPIO_OUT_REG, SigA);
    Serial.println(SigAstate);
    delayMicroseconds(pulse);
    digitalWrite(SigA, LOW);
    SigAstate = bitRead(GPIO_OUT_REG, SigA);
    Serial.println(SigAstate);
    delayMicroseconds(100);
  }
  delayMicroseconds(10000);
  input1state = digitalRead(input1);
  while(input1state == 1)
  {
    ledcWrite(0, 0); //set clock0 to 0 dutycycle
    delayMicroseconds(1000); //debounce
    input1state = digitalRead(input1);//check button
  }
  ledcWrite(0, 1); //allow pulses on SigB
  input2state = digitalRead(input2);
  while(input2state == 1)
  {
    while(SigBstate==0)
    {
      //hold to prevent unalignment with SigB
      SigBstate == bitRead(GPIO_OUT_REG, SigB);
    }
    SigBstate = 0;
    pulse = 0;
    for(i=18; i>=0; i--) //run pulses starting with largest
    {
      pulse = a + (50*i);
      digitalWrite(SigA, HIGH);
      delayMicroseconds(pulse);
      digitalWrite(SigA, LOW);
      delayMicroseconds(100);
    }
    delayMicroseconds(10000);
    input2state = digitalRead(input2);
  }
  
 
}
