/*
 * Filename: 8_3_Fire_Alarm
 * Function: Use flame sensor, LM35 temperature sensor, buzzer to make fire alarm
 * Compile IDE: ARDUINO 2.3.4
 * Author: https://www.keyestudio.com/ 
*/

const int Buzzer_Pin = 13;  // the buzzer pin
const int Flame_Pin = 35;   //set flame sensor pin to GPIO35

const int LM35_Pin = 36;        //set lm35 pin to GPIO36
float temperature = 0;          //set variable temperature initial value to 0
long value = 0;                 //set variable value initial value to 0
float constant = 5.0 / 4095.0;  //Set the analog value constant for the calculated temperature

void setup() {
  pinMode(Buzzer_Pin, OUTPUT);  // Set as output
  pinMode(LM35_Pin, INPUT);     //set LM35_Pin to input
  pinMode(Flame_Pin, INPUT);    //set flame sensor pin to input
  Serial.begin(9600);
}

void loop() {

  int analogVal = analogRead(Flame_Pin);  //Read the analog signal of the flame sensor

  value = analogRead(LM35_Pin);            //Read analog input
  temperature = (value * constant * 100);  //Calculate temperature values
  
  if (analogVal > 500 || temperature > 50) {
    digitalWrite(Buzzer_Pin, HIGH);  //buzzer alarms
  } else {
    digitalWrite(Buzzer_Pin, LOW);  //buzzer off
  }
  delay(100);
}