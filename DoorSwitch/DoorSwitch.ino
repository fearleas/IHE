#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

ESP8266WiFiMulti WiFiMulti;

IPAddress server(83, 82, 172, 77);

WiFiClient wifiClient;
PubSubClient client(wifiClient);

const int switchPin = 2;
const int ledPin = 12;

//------------------------------------------------------------
//                      MQTT CONNECTION
//------------------------------------------------------------
void reconnect() {
  while (!client.connected()) {
    if (client.connect("WEMOS_DOOR","admin","Yu0h52bV1")) {
      client.publish("deur","deur verbonden");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void setup()
{
  Serial.begin(115200);
  delay(10);

  pinMode(switchPin, INPUT);

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

  if(digitalRead(switchPin) == HIGH)
    client.publish("deur","warning");
}
