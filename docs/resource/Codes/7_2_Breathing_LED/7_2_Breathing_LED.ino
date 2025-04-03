/*
 * Filename: 7_2_Breathing_LED
 * Function: Make led light fade in and out, just like breathing.
 * Compiling IDE：ARDUINO 2.3.4
 * Author: https://www.keyestudio.com/
*/
const int PWM_LED_Pin = 26;  // The GPIO pin for the LED

void setup() {
  pinMode(PWM_LED_Pin, OUTPUT);  // Set LED pin to output
}

void loop() {
  for (int i = 0; i < 255; i++) {  //make light fade in
    analogWrite(PWM_LED_Pin, i);   //Output PWM
    delay(10);                     //delay 10ms
  }
  for (int i = 255; i >= 0; i--) {  //make light fade out
    analogWrite(PWM_LED_Pin, i);    //Output PWM
    delay(10);                      //delay 10ms
  }
}