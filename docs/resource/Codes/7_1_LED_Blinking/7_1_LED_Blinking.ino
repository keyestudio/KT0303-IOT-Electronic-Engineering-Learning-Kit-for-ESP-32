/*
 * File name: 7_1_LED_Blinking
 * Function: LED blinks 1s
 * Compiling IDE: ARDUINO 2.3.4
 * Author: https://www.keyestudio.com/
*/
const int Red_LED_Pin = 26; // Define LED pin to IO26.

void setup(){
  pinMode(Red_LED_Pin, OUTPUT); // Set LED pin to output
}

void loop(){
  digitalWrite(Red_LED_Pin, HIGH); // LED on.
  delay(1000); // Delay 1s.
  digitalWrite(Red_LED_Pin, LOW); // LED off.
  delay(1000); // Delay 1s.
}