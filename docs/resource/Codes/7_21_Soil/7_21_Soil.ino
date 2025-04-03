/*  
 * Filename   : 7_21_Soil
 * Function   : read soil humidity values
 * Compiling IDE: ARDUINO 2.3.4
 * Author: https://www.keyestudio.com/ 
*/
const int Soil_Pin = 33;  //set soil humidity sensor to pin IO33

void setup() {
Serial.begin(9600); 
pinMode(Soil_Pin, INPUT);  //set pin to input

}

void loop() {
  //read sensor analog value
  int soil_Val = analogRead(Soil_Pin);  
  //print the humidity values
  Serial.print("Soil Humidity: ");  
  Serial.println(soil_Val);
  delay(100);
}