#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

ESP8266WiFiMulti WiFiMulti;

IPAddress server(83, 82, 172, 77);

WiFiClient wifiClient;
PubSubClient client(wifiClient);

unsigned long echo = 0;
unsigned long ultrasoundValue = 0;

int rDistance = 15;       //binnen deze afstand is er wel een pan
int lTime = 1;            // tijd dat fornuis aan en leeg mag zijn in min 
                          //*?koelt niet direct af PROBLEEM!!!*?

int mDistance = 0;        //gemeten afstand
int heat = 0;             // wel of geen hitte
boolean message = false;  // is er al een bericht  verstuurd?


int ultrasoundPin = 4;   //D2
int heatPin = 0;         //D3
int relaisPin = 16;      //D0

//------------------------------------------------------------
//                      MQTT CONNECTION
//------------------------------------------------------------
void reconnect() {
  while (!client.connected()) {
    if (client.connect("WEMOS","admin","Yu0h52bV1")) {
      client.publish("fornuis","fornuis verbonden");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

long ultrasound() // ultrasound sensor
{
  pinMode(ultrasoundPin, OUTPUT);         // Switch signalpin to output
  digitalWrite(ultrasoundPin, LOW);       // Send low pulse
  delayMicroseconds(2);                   // Wait for 2 microseconds
  digitalWrite(ultrasoundPin, HIGH);      // Send high pulse
  delayMicroseconds(5);                   // Wait for 5 microseconds
  digitalWrite(ultrasoundPin, LOW);       // Holdoff
  pinMode(ultrasoundPin, INPUT);          // Switch signalpin to input
  digitalWrite(ultrasoundPin, HIGH);      // Turn on pullup resistor
  echo = pulseIn(ultrasoundPin, HIGH);    //Listen for echo
  ultrasoundValue = (echo / 58.138);      // convert to cm
  return ultrasoundValue;
}

void setup()
{
  Serial.begin(115200);
  delay(10);

  pinMode(ultrasoundPin, OUTPUT);         //Ultrasound
  pinMode(heatPin, INPUT);                //Hittesensor
  pinMode(relaisPin, OUTPUT);             //Relais

  //------------------------------------------------------------
  //                      WIFI CONNECTION
  //------------------------------------------------------------

  WiFiMulti.addAP("O&O Project", "IoT2017");

  while(WiFiMulti.run() != WL_CONNECTED) {
       Serial.print(".");
       delay(500);
  }
  
  client.setServer(server, 1883);         //connect to broker
  delay(1500);
}

void loop()
{
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  mDistance = ultrasound();               //afstand pan-sensor
  heat = digitalRead(heatPin);            //warmte test.
  if (mDistance > rDistance && heat == 1)
  {
    delay(lTime * 60000);
    mDistance = ultrasound();               //afstand pan-sensor
    heat = digitalRead(heatPin);            //warmte test.
    if (mDistance > rDistance && heat == 1 && !message)
    {
      message == true;
      client.publish("fornuis","warning");
      digitalWrite(relaisPin, HIGH);
    }
  }
}
