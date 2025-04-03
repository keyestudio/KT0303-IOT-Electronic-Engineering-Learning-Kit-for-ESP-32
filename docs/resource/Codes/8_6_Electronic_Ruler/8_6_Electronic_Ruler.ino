/*  
 * Filename: 8_6_Electronic_Ruler
 * Function: Use the ultrasonic sensor to measure distances
 * Compile IDE: ARDUINO 2.3.4
 * Author: https://www.keyestudio.com/ 
*/
#include <GyverOLED.h>  // Import GyverOLED library for controlling OLED display

GyverOLED<SSH1106_128x64> oled;  // Create an OLED object specifying the display model SSH1106 with a resolution of 128x64

// Define pins for the ultrasonic sensor
const int trigPin = 13;
const int echoPin = 12;

// Function prototype for reading sensor data
float readSensorData();

void setup() {
  oled.init();   // Initialize the OLED display
  oled.clear();  // Clear the screen, making sure it is initially blank
  // Set echoPin as input and trigPin as output
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  // Read distance from the ultrasonic sensor
  float distance = readSensorData();

  oled.clear();               //Clear display
  oled.setScale(2);           // Set the font size to 2
  oled.setCursorXY(0, 0);     // Set display position
  oled.println("Distance:");  // wrap to display
  oled.print(distance);       // Display distance value
  oled.println("CM");         // wrap to display
  oled.update();              // Refresh display
  delay(100);
}

// Function to read data from the ultrasonic sensor
float readSensorData() {
  // Trigger a low signal before sending a high signal
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Send a 10-microsecond high signal to the trigPin
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  // Return to low signal
  digitalWrite(trigPin, LOW);

  // Measure the duration of the high signal on the echoPin
  unsigned long microsecond = pulseIn(echoPin, HIGH);
  // Calculate the distance using the speed of sound (29.00µs per centimeter)
  float distance = microsecond / 29.00 / 2;
  // Return the calculated distance
  return distance;
}