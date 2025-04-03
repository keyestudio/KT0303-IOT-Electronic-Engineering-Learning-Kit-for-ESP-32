/*
 * Filename: 7_4_RGB_LED
 * Functions: Control RGB LED to emit different colors of light
 * Compiling IDE: ARDUINO 2.3.4
 * Author: https://www.keyestudio.com/ 
*/

const int Red_LED_Pin = 27;   //set red LED pin
const int Blue_LED_Pin = 26;   //set blue LED pin
const int Green_LED_Pin = 25;   //set green LED pin


void setup() {
  //set pins to output
  pinMode(Red_LED_Pin,OUTPUT);
  pinMode(Blue_LED_Pin,OUTPUT);
  pinMode(Green_LED_Pin,OUTPUT);
}

void loop() {
  setColor(255, 0, 0); // Red
  delay(1000);
  setColor(0, 255, 0); // Green
  delay(1000);
  setColor(0, 0, 255); // Blue
  delay(1000);
  setColor(255, 255, 0); // Yellow
  delay(1000);
  setColor(255, 0, 255); // Purple
  delay(1000);
  setColor(0, 255, 255); // Cyan
  delay(1000);
}

/*
  function: setColor
  It integrates the RGB light control code into a function, and control it via (0-255,0-255,0-255)
*/
void setColor(int red, int green, int blue) {
  analogWrite(Red_LED_Pin,red);
  analogWrite(Green_LED_Pin,green);
  analogWrite(Blue_LED_Pin,blue);
}