unsigned long echo = 0;
unsigned long ultrasoundValue = 0;
boolean stroom = false;
int knopwaarde = 0;

int ultraSoundSignal  = 9; 
int knopInput = 7;
int ledOutput = 5;


void setup()
{
   Serial.begin(9600);
   pinMode(ultraSoundSignal,OUTPUT);
   pinMode(ledOutput, OUTPUT);
   pinMode(knopInput, INPUT);
}

long ping()
{ 
   pinMode(ultraSoundSignal, OUTPUT); // Switch signalpin to output
   digitalWrite(ultraSoundSignal, LOW); // Send low pulse 
   delayMicroseconds(2); // Wait for 2 microseconds
   digitalWrite(ultraSoundSignal, HIGH); // Send high pulse
   delayMicroseconds(5); // Wait for 5 microseconds
   digitalWrite(ultraSoundSignal, LOW); // Holdoff
   pinMode(ultraSoundSignal, INPUT); // Switch signalpin to input
   digitalWrite(ultraSoundSignal, HIGH); // Turn on pullup resistor
   // please note that pulseIn has a 1sec timeout, which may
   // not be desirable. Depending on your sensor specs, you
   // can likely bound the time like this -- marcmerlin
   // echo = pulseIn(ultraSoundSignal, HIGH, 38000)
   echo = pulseIn(ultraSoundSignal, HIGH); //Listen for echo
   ultrasoundValue = (echo / 58.138); //convert to CM then to inches
   return ultrasoundValue;
}

void LED()
{
  digitalWrite(ledOutput, HIGH);
}

void loop()
{
   /*
   int x = 0;
   x = ping();
   delay(250); //delay 1/4 seconds.
   if (digitalRead(knopInput) == HIGH)
   {
    stroom = true;
    db = 1;
   }
   else
   {
    stroom = false;
    db = 0;
   }
   if (stroom && x < 10)
   {
    digitalWrite(ledOutput, HIGH);
   }
   else
   {
    digitalWrite(ledOutput, LOW);
   }
   Serial.println(x + "    " + db);
   */
   
   
   int x = 0;
   x = ping();
   Serial.println(x);
   delay(250); 
   
   knopwaarde = digitalRead(knopInput);
   if (x < 10 && knopwaarde == HIGH)
   {
    digitalWrite(ledOutput, HIGH);
   }
   else
   {
    digitalWrite(ledOutput, LOW);
   }
   //delay 1/4 seconds.
}
