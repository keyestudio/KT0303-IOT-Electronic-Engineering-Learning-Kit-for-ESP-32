/*  
 * Filename: 9_6_environmental_monitoring
 * Function: use the network to read the illuminance, temperature, water level, soil moisture in the greenhouse, (relay + pump) watering, (servo) opening the Windows for ventilation
 * Compile IDE: ARDUINO 2.3.4
 * Author: https://www.keyestudio.com/ 
*/
#include <Arduino.h>
#include <WiFi.h>
#include <ESP32Servo.h>
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
const char* topic_light_value = "esp32/light_value";              //photoresistor data topic
const char* topic_water_level_value = "esp32/water_level_value";  //water level sensor data topic
const char* topic_soil_value = "esp32/soil_value";                //soil humidity sensor data topic
const char* topic_temperature_value = "esp32/temperature_value";  //temperature sensor data topic
const char* topic_relay = "esp32/control_relay";                  //relay control topic
const char* topic_servo = "esp32/control_servo";                  //servo control topic

const int light_sensor_pin = 33;        //photoresistor pin
const int water_level_sensor_pin = 34;  // water level sensor pin
const int soil_sensor_pin = 35;         // soil humidity sensor pin
const int temperature_sensor_pin = 36;  // temperature sensor pin
const int relay_pin = 12;               //relay pin
const int servo_pin = 13;               //servo pin

Servo myservo;  // create servo object to control a servo

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

  // control LED according to the received message
  if (message == "relay-on") {  //relay on, water pump on
    Serial.println("Turning on water pump");
    digitalWrite(relay_pin, HIGH);
  } else if (message == "relay-off") {  //relay off, water pump off
    Serial.println("Turning off water pump");
    digitalWrite(relay_pin, LOW);
  } else if (message == "servo-on") {  //relay off, servo on
    myservo.write(180);                // set servo to 180°
    delay(500);
  } else if (message == "servo-off") {  //relay off, servo off
    myservo.write(0);                   // set servo to 0°
    delay(500);
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
      mqttClient.subscribe(topic_servo);  //subscribe servo control 
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
  //set sensor pins to input
  pinMode(light_sensor_pin, INPUT);
  pinMode(water_level_sensor_pin, INPUT);
  pinMode(soil_sensor_pin, INPUT);
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
  myservo.attach(servo_pin);  //attaches the servo on pin to the servo object
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
    int light_level_sensor_value = analogRead(light_sensor_pin);
    int water_level_sensor_value = analogRead(water_level_sensor_pin);
    int soil_sensor_value = analogRead(soil_sensor_pin);

    temperature_value = analogRead(temperature_sensor_pin);
    temperature = (temperature_value * constant * 100);  //Calculate analog temperature value

    // Convert the value to a string
    String light_sensor_value_str = String(light_level_sensor_value);
    String water_level_sensor_value_str = String(water_level_sensor_value);
    String soil_sensor_value_str = String(soil_sensor_value);
    String temperature_sensor_value_str = String(temperature);

    //send data
    mqttClient.publish(topic_light_value, light_sensor_value_str.c_str());
    mqttClient.publish(topic_water_level_value, water_level_sensor_value_str.c_str());
    mqttClient.publish(topic_soil_value, soil_sensor_value_str.c_str());
    mqttClient.publish(topic_temperature_value, temperature_sensor_value_str.c_str());
  }
}