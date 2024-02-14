
//code el esp32 node mcu
#include <EEPROM.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>
#include <SoftwareSerial.h>
SoftwareSerial mySerial (D1,D2);//rx-->d2 , tx-->d1

 
// Connect to the WiFi
const char* ssid = "Midoehab";                           //!!!!!!!!!!!!!!!!!!!!!
const char* password = "wolfTEAM1";                //!!!!!!!!!!!!!!!!!!!!!
const char* mqtt_server = "172.201.248.158";                 //!!!!!!!!!!!!!!!!!!!!!

 
WiFiClient espClient;
PubSubClient client(espClient);
void callback(char* topic, byte* payload, unsigned int length) {
 
  // Convert payload to an integer
  int receivedInt = 0;
  for (int i = 0; i < length; i++) {
    receivedInt = receivedInt * 10 + (payload[i] - '0');
  }

  
  Serial.println(receivedInt);

  // Convert the integer to a string
  String intAsString = String(receivedInt);


}
void setup_wifi() {
  delay(10);
  Serial.println("Connecting to WiFi");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting...");
  }
  Serial.println("Connected to WiFi");
}

void reconnect() {
 // Loop until we're reconnected
 while (!client.connected()) {
 Serial.print("Attempting MQTT connection...");
 // Attempt to connect
 if (client.connect("ESP8266 Client")) {
  Serial.println("connected");
  // ... and subscribe to topic
  client.subscribe("water_quality/threshold");
  
 } else {
  Serial.print("failed, rc=");
  Serial.print(client.state());
  Serial.println(" try again in 5 seconds");
  // Wait 5 seconds before retrying
  delay(5000);
  }
 }
}
 void setup()
{
 Serial.begin(115200);
 setup_wifi();
  mySerial.begin(9600);//arduino's
 //ip and port no
 client.setServer(mqtt_server, 1883);
 client.setCallback(callback);

}
 
void loop()
{
  //get arduino's msg
  String msg=mySerial.readStringUntil('\r');
  client.publish("water_quality/pH",msg.c_str());
 if (!client.connected()) {
  reconnect();
 }
 client.loop();
}
 

 
 

 
