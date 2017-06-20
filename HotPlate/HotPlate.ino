unsigned long echo = 0;
unsigned long ultrasoundValue = 0;

int rDistance = 15; //binnen deze afstand is er wel een pan
int lTime = 1;      // tijd dat fornuis aan en leeg mag zijn in min 
                    //*?koelt niet direct af PROBLEEM!!!*?

int mDistance = 0;  //gemeten afstand
int heat = 0;       // wel of geen hitte
boolean message = false; // is er al een bericht  verstuurd?


int ultrasoundPin = 4; //D2
int heatPin = 0;       //D3
int relaisPin = 16;    //D0
int buttonPin = 2;     //D4

void setup()
{
  Serial.begin(9600);
  pinMode(ultrasoundPin, OUTPUT);           //Ultrasound
  pinMode(heatPin, INPUT);                  //Hittesensor
  pinMode(relaisPin, OUTPUT);               //Relais
  pinMode(buttonPin, INPUT);                 //Knop
}

long ultrasound() // ultrasound sensor
{
  pinMode(ultrasoundPin, OUTPUT); // Switch signalpin to output
  digitalWrite(ultrasoundPin, LOW); // Send low pulse
  delayMicroseconds(2); // Wait for 2 microseconds
  digitalWrite(ultrasoundPin, HIGH); // Send high pulse
  delayMicroseconds(5); // Wait for 5 microseconds
  digitalWrite(ultrasoundPin, LOW); // Holdoff
  pinMode(ultrasoundPin, INPUT); // Switch signalpin to input
  digitalWrite(ultrasoundPin, HIGH); // Turn on pullup resistor
  echo = pulseIn(ultrasoundPin, HIGH); //Listen for echo
  ultrasoundValue = (echo / 58.138); // convert to cm
  return ultrasoundValue;
}

void loop()
{
  mDistance = ultrasound(); //afstand pan-sensor
  heat = digitalRead(heatPin); //warmte test.
  if (mDistance > rDistance && heat == 1)
  {
    delay(lTime * 60000);
    if (mDistance > rDistance && heat == 1 && !message)
    {
      message == true;
      //nigel code voor bericht naar server
      digitalWrite(relaisPin, HIGH);
    }
  }
  if(digitalRead(buttonPin == HIGH))
  {
    digitalWrite(relaisPin, LOW);
    message == false;
  }
}
