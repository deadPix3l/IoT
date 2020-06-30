/**
 * Adapted From:
 * HX711 library for Arduino - example file
 * https://github.com/bogde/HX711
 *
 * MIT License
 * (c) 2018 Bogdan Necula
**/
#include <ESP8266WiFi.h>
#include "PubSubClient.h"
#include "HX711.h"


// HX711 circuit wiring
const int LOADCELL_DOUT_PIN = 4;
const int LOADCELL_SCK_PIN = 5;
HX711 scale;

// Wifi Connection
const char* ssid = "[redacted]";
const char* password =  "[redacted]";

//MQTT Info
const char* mqttServer = "[redacted]";
const int mqttPort = 1883;
const char* mqttUser = "[redacted]";
const char* mqttPassword = "[redacted]";

char data[64] = "";

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(9600);
  Serial.println("HX711 Initiallizing...");

  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale(2280.f);  // this value is obtained by calibrating the scale with known weights; see the README for details
  scale.tare();             // reset the scale to 0

  // Connecting to Wifi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("WiFi Connected!");

  // Connecting to MQTT
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);

  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");

    if (client.connect("BedScale", mqttUser, mqttPassword )) {

      Serial.println("MQTT connected");

    } else {

      Serial.print("MQTT Connect: failed with state ");
      Serial.print(client.state());
      delay(2000);

    }
  }

  //client.publish("sensors/bedscalet", "Hello from ESP8266");
  client.subscribe("sensors/bedscale");

}

void loop() {
//  Serial.print("one reading:\t");
//  Serial.print(scale.get_units(), 1);

  int scaleval = scale.get_units(10);
  sprintf(data, "%f", -scale.get_units(10));
  Serial.println(data);
  client.publish("sensors/bedscale", data);

  scale.power_down();             // put the ADC in sleep mode
  delay(3000);
  scale.power_up();
}

void callback(char* topic, byte* payload, unsigned int length) {

  Serial.print("Message arrived in topic: ");
  Serial.println(topic);

  Serial.print("Message:");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }

  Serial.println();
  Serial.println("-----------------------");

}
