/*  
 * Filename: 9_7_Forest_fire_prevention
 * Function: use the network to read the data of the flame sensor and temperature sensor in the forest, and we can know the first time there is a fire according to the data provided by the sensor.
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
const char* topic_flame_value = "esp32/flame_value";                //flame sensor data topic
const char* topic_temperature_value = "esp32/temperature_value";  //temperature sensor data topic

const int flame_sensor_pin = 35;         // flame sensor pin
const int temperature_sensor_pin = 36;  // temperature sensor pin



float temperature = 0;          //set variable temperature initial value to 0
long temperature_value = 0;     //set variable value initial value to 0
float constant = 5.0 / 4095.0;  //Define the analog constant for the calculated temperature

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
  //set sensor pins to input
  pinMode(flame_sensor_pin, INPUT);
  pinMode(temperature_sensor_pin, INPUT);

  // connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("Connected to Wi-Fi");

  setupMQTT();                // Set up the MQTT client
}

void loop() {
  if (!mqttClient.connected()) {  // If MQTT broker is not connected
    reconnect();                  // Attempt to reconnect
  }
  mqttClient.loop();  // Keep MQTT client connections active

  long now = millis();
  if (now - previous_time > 1000) {  // Publish every 1 second
    previous_time = now;

    // Read the sensor value
    int flame_sensor_value = analogRead(flame_sensor_pin);

    temperature_value = analogRead(temperature_sensor_pin);
    temperature = (temperature_value * constant * 100);  //Calculate analog temperature value

    // Convert the value to a string
    String flame_sensor_value_str = String(flame_sensor_value);
    String temperature_sensor_value_str = String(temperature);

    //send data
    mqttClient.publish(topic_flame_value, flame_sensor_value_str.c_str());
    mqttClient.publish(topic_temperature_value, temperature_sensor_value_str.c_str());
  }
}