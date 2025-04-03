/*
 * Filename   : 7_7_Read_Button
 * Function   : read button value
 * Compiling IDE: ARDUINO 2.3.4
 * Author: https://www.keyestudio.com/
*/
const int Button_Pin = 14;  // set button pin to IO14
int val = 0;                // store button value

void setup() {
  Serial.begin(9600);          // set baud rate to 9600
  pinMode(Button_Pin, INPUT);  // set button pin to input
}

void loop() {
  val = digitalRead(Button_Pin);  // read button value and assign it to val
  Serial.print(val);              // print val on the monitor
  if (val == 0) {                 // press button, read low and print it out
    Serial.print("    ");
    Serial.println("Button Down!");  // print a message of button being pressed
    delay(100);
  } else {  // val is not equal to 0: button is released
    Serial.print("    ");
    Serial.println("Release the button!");  // print a message of button being released
    delay(100);
  }
}