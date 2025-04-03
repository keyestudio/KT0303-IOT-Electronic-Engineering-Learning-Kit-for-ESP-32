/*
 * Filename: 7_5_Beep
 * Function: Control the sound of the active buzzer
 * Compiling IDE: ARDUINO 2.3.4
 * Author: https://www.keyestudio.com/
*/
const int Buzzer_Pin = 13;  // the buzzer pin

void setup() {
  pinMode(Buzzer_Pin, OUTPUT);  // Set as output
}

void loop() {

  digitalWrite(Buzzer_Pin, HIGH);  //active buzzer sound
  delay(2000);                     //delay 2S
  digitalWrite(Buzzer_Pin, LOW);   //active buzzer off
  delay(2000);                     //delay 2S
}