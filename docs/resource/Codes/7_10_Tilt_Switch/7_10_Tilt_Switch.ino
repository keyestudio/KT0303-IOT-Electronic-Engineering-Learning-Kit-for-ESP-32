/*
 * Filename   : 7_10_Tilt_Switch
 * Function   : read tilt sensor value
 * Compiling IDE: ARDUINO 2.3.4
 * Author: https://www.keyestudio.com/ 
*/
int Switch_Pin = 14; // set tilt switch pin to IO14
int val = 0;       // store tilt switch value

void setup(){
  Serial.begin(9600); // set baud rate to 9600
  pinMode(Switch_Pin, INPUT); // set tilt switch pin to input
} 

void loop(){
  val = digitalRead(Switch_Pin); // read tilt switch value and assign it to val
  Serial.print(val);  // print val
  if (val == 1) {  // tilt switch tilts: read high and print it out
    Serial.print("    ");  
    Serial.println("Tilt"); // print tilt
    delay(100); 
  }
  else {  // tilt switch does not tilt: read low
    Serial.print("    ");
    Serial.println("No tilt");
    delay(100);
  }
}