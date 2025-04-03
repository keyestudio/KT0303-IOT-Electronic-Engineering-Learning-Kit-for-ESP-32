/*  
 * Filename   : 7_22_Water_Level_Sensor
 * Function   : read water level sensor value
 * Compiling IDE: ARDUINO 2.3.4
 * Author: https://www.keyestudio.com/ 
*/
const int Water_Level_Pin = 34;  //set sensor pin to IO34

void setup() {
Serial.begin(9600); 
pinMode(Water_Level_Pin, INPUT);  //set the pin to input

}

void loop() {
  //read the water level sensor value
  int waterLevel_Val = analogRead(Water_Level_Pin);  
  //print the value
  Serial.print("Water Level Value: ");  
  Serial.println(waterLevel_Val);
  delay(100);
}