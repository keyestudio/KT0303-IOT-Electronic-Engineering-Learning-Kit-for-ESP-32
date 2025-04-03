/*  
 * Filename   : 7_9_Flame_Sensor
 * Function   : read flame sensor value
 * Compiling IDE: ARDUINO 2.3.4
 * Author: https://www.keyestudio.com/
*/
const int Flame_Pin = 36;   //set flame sensor pin to GPIO36

void setup() {
  Serial.begin(9600);   //set baud rate to 9600
  pinMode(Flame_Pin, INPUT);    //set flame sensor pin to input
}

void loop() {
  int analogVal = analogRead(Flame_Pin);    //read flame sensor analog signal
  Serial.print("Analog Val: ");    //print “Analog Val”
  Serial.println(analogVal);    //print analogVal value
  delay(200);
}