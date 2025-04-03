/*  
 * Filename   : 7_17_Set_Servo_Angle
 * Function   : servo rotation, from 0 degrees to 90 degrees to 180 degrees in turn
 * Compiling IDE: ARDUINO 2.3.4
 * Author: https://www.keyestudio.com/
*/
#include <ESP32Servo.h>

Servo myservo;             // create servo object to control a servo
const int Servo_Pin = 4;  // GPIO pin used to connect the servo control (digital out)

void setup() {
  myservo.attach(Servo_Pin);   //attaches the servo on pin to the servo object
}

void loop() {
  myservo.write(0);    // set servo angle to 0 degree
  delay(1000);         // delay 1s
  myservo.write(90);   // set servo angle to 90 degree
  delay(1000);         // delay 1s
  myservo.write(180);  // set servo angle to 180 degree
  delay(1000);         // delay 1s
}
