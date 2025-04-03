/*  
 * Filename   : 7_11_Photoresistor
 * Function   : read photoresistor value to detect light intensity
 * Compiling IDE: ARDUINO 2.3.4
 * Author: https://www.keyestudio.com/
*/
const int Photoresistor_Pin = 36;   //set photoresistor pin to GPIO36

void setup() {
  Serial.begin(9600);   //set baud rate to 9600
  pinMode(Photoresistor_Pin, INPUT);    //set photoresistor pin to input
}

void loop() {
  int PhotoresistorVal = analogRead(Photoresistor_Pin);    //read photoresistor analog signal
  Serial.print("Photoresistor Val: ");    //print "Photoresistor Val:"
  Serial.println(PhotoresistorVal);    //show PhotoresistorVal value
  delay(200);
}