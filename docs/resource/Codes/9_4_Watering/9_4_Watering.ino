/*  
 * Filename: 9_4_Watering
 * Function: use the network to read the analog humidity values of the plants and remotely control the water pump
 * Compile IDE: ARDUINO 2.3.4
 * Author: https://www.keyestudio.com/ 
*/
#include <Arduino.h>
#include <WiFi.h>
// Use WiFiClient instead of WiFiClientSecure because this example uses an unencrypted connection
#include <PubSubClient.h>  // Include MQTT client libraries for connecting and managing MQTT messages

// Wi-Fi credentials
const char* ssid = "your SSID";    // Wi-Fi SSID, network name
const char* password = "Password"; // Wi-Fi passwords

// MQTT broker
const char* mqtt_broker = "test.mosquitto.org";  // a public Mosquitto MQTT broker
const int mqtt_port = 1883;                      // MQTT uses port 1883 for an unencrypted connection

//Ensure that the clientId is unique; otherwise, connection conflicts may occur
String clientId = "ESP32Client-keyes";

// Handle MQTT topics for sending and receiving control signals
const char* topic_soil_value = "esp32/soil_value";  //sensor data topic
const char* topic_relay = "esp32/control_relay";    //relay control 

const int soil_sensor_pin = 36;  // soil humidity sensor pin
const int relay_pin = 12;        //relay pin

// Create WiFi client and MQTT client instances
WiFiClient wifiClient;                // Use normal WiFiClient to connect
PubSubClient mqttClient(wifiClient);  // Instantiate the MQTT client using the WiFi client

// Define a time variable to publish sensor data periodically
long previous_time = 0;  // store the last time data was sent

// MQTT message callback function that processes received messages
void mqttCallback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);  // Topic of the output message
  Serial.print("]: ");
  String message;
  // Convert the received byte data to a string
  for (int i = 0; i < length; i++) {
    message += (char)payload[i];
  }
  Serial.print("message:");
  Serial.println(message);

  // control LED according to the received message
  if (message == "relay-on") {  //relay on, water pump on
    Serial.println("Turning on water pump");
    digitalWrite(relay_pin, HIGH);
  } else if (message == "relay-off") {  //relay off, water pump off
    Serial.println("Turning off water pump");
    digitalWrite(relay_pin, LOW);
  }
}

// Set up the MQTT client
void setupMQTT() {
  mqttClient.setServer(mqtt_broker, mqtt_port);  // Set the address and port of the MQTT broker
  mqttClient.setCallback(mqttCallback);          // Set the message callback function
}

// try to re-connect to MQTT broker
void reconnect() {
  Serial.println("Connecting to MQTT Broker...");
  while (!mqttClient.connected()) {  // If it is not connected, the connection attempt is repeated
    Serial.println("Reconnecting to MQTT Broker...");
    clientId += String(random(0xffff), HEX);  // If it is not connected, the connection attempt is repeated

    if (mqttClient.connect(clientId.c_str())) {  // Connect to the broker through clientId
      Serial.println("Connected to MQTT Broker.");

      // subscribe the topic
      mqttClient.subscribe(topic_relay);  //subscribe relay control 
    } else {
      Serial.print("Failed, rc=");
      Serial.print(mqttClient.state());  // Print the reason for the connection failure
      Serial.println(" try again in 5 seconds");
      delay(5000);  // Retry the connection every 5 seconds
    }
  }
}

void setup() {
  Serial.begin(115200);  // Retry the connection every 5 seconds
  // set relay pin to output
  pinMode(relay_pin, OUTPUT);
  // set soil humidity sensor pin to input
  pinMode(soil_sensor_pin, INPUT);
  // connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("Connected to Wi-Fi");

  setupMQTT();  // Set up the MQTT client
}

void loop() {
  if (!mqttClient.connected()) {// If MQTT broker is not connected
    reconnect(); // Attempt to reconnect
  }
  mqttClient.loop(); // Keep MQTT client connections active

  long now = millis();
  if (now - previous_time > 1000) {  // Publish every 1 second
    previous_time = now;

    // Read the sensor value
    int sensor_value = analogRead(soil_sensor_pin);

    // Convert the value to a string
    String sensor_value_str = String(sensor_value);
    Serial.println(sensor_value_str);

    mqttClient.publish(topic_soil_value, sensor_value_str.c_str());
  }
}