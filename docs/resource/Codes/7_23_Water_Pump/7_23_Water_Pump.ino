/*  
 * Filename   : 7_23_Water_Pump
 * Function   : relay controls 5V to power water pump
 * Compiling IDE: ARDUINO 2.3.4
 * Author: https://www.keyestudio.com/
*/
const int Relay_Pin = 12;  // set relay pin to IO12

void setup() {
  pinMode(Relay_Pin, OUTPUT);    // set relay pin to output
  digitalWrite(Relay_Pin, LOW);  // set relay initial state to off
}
void loop() {
  digitalWrite(Relay_Pin, HIGH);  //set relay NO off, the water pump works
  delay(2000);                    //delay 2s
  digitalWrite(Relay_Pin, LOW);   //set relay NO on, the water pump stops working
  delay(2000);                    //delay 2s
}

