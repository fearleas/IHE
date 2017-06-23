#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

ESP8266WiFiMulti WiFiMulti;

WiFiClient wifiClient;
PubSubClient client(wifiClient);

const int switchPin = 5;


//------------------------------------------------------------
//                      MQTT CONNECTION
//------------------------------------------------------------
void reconnect() {
  while (!client.connected()) {
    if (client.connect("Deur_Jan","twinwxduz","Ug2TbfH9g53")) {
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

  WiFiMulti.addAP("kevin", "12pbeek12");

  while(WiFiMulti.run() != WL_CONNECTED) {
       Serial.print(".");
       delay(500);
  }
  
  client.setServer(m20.cloudmqtt.com, 14395);         //connect to broker
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
