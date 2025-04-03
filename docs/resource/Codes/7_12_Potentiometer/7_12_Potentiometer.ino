/*  
 * Filename   : 7_12_Potentiometer
 * Function   : read Potentiometer value
 * Compiling IDE: ARDUINO 2.3.4
 * Author: https://www.keyestudio.com/
*/
const int Pot_Pin = 36;   //set Potentiometer pin to GPIO36

void setup() {
  Serial.begin(9600);   //set baud rate to 9600
  pinMode(Pot_Pin, INPUT);    //set the pin to input
}

void loop() {
  int PotVal = analogRead(Pot_Pin);    //read Potentiometer analog signal
  Serial.print("Potentiometer Val: ");    //print Potentiometer Val:
  Serial.println(PotVal);    //show PotVal value
  delay(200);
}