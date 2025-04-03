/*
 * Filename: 7_3_Traffic_Lights
 * Fuction: Traffic Lights
 * Compiling IDE: ARDUINO 2.3.4
 * Author: https://www.keyestudio.com/ 
*/
const int Red_LED_Pin = 13;   //Set the red LED pin
const int Yellow_LED_Pin = 14;   //Set the yellow LED pin
const int Green_LED_Pin = 16;   //Set the green LED pin

void setup() {
  pinMode(Red_LED_Pin, OUTPUT);
  pinMode(Yellow_LED_Pin, OUTPUT);
  pinMode(Green_LED_Pin, OUTPUT);
}

void loop() {
   digitalWrite(Green_LED_Pin, HIGH);// turn on green LED
   delay(5000);// delay 5 s
   digitalWrite(Green_LED_Pin, LOW);// 
   delay(500);// delay 0.5 s
   for(int i=0;i<3;i++)// blink 3 times.
   {
     digitalWrite(Yellow_LED_Pin, HIGH);// turn on yellow LED
     delay(500);// delay 0.5 s
     digitalWrite(Yellow_LED_Pin, LOW);// turn off yellow LED
     delay(500);// delay 0.5 s
   } 
   digitalWrite(Red_LED_Pin, HIGH);// turn on red LED
   delay(5000);// delay 5 s
   digitalWrite(Red_LED_Pin, LOW); // turn off red LED
   delay(500);// delay 0.5 s
}