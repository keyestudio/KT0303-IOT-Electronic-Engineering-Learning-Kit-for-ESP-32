/*  
 * Filename   : 7_16_Relay_Control
 * Function   : relay controls 5V to power LED
 * Compiling IDE: ARDUINO 2.3.4
 * Author: https://www.keyestudio.com/
*/
const int Relay_Pin = 12;  // set relay pin to IO12

void setup() {
  pinMode(Relay_Pin, OUTPUT);    // set relay pin to output
  digitalWrite(Relay_Pin, LOW);  // set relay initial state to off
}
void loop() {
  digitalWrite(Relay_Pin, HIGH);  //turn off relay NC, red led on
  delay(1000);                    //delay 1s
  digitalWrite(Relay_Pin, LOW);   //tunr on relay NO, red led off
  delay(1000);                    //delay 1s
}
