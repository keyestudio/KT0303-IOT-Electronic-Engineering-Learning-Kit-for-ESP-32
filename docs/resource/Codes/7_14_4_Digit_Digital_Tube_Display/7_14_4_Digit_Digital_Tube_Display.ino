/*
 * Filename   : 7_14_4_Digit_Digital_Tube_Display
 * Function   : 4-bit digital tube shows 0000-9999
 * Compiling IDE: ARDUINO 2.3.4
 * Function：digitalTube.DisplayNum(val); Used to display numbers, when used, replace val with the number you want to display
 * Author: https://www.keyestudio.com/ 
*/
#include "DigitalTube.h"

//set digital tube pins
const displayPins myPins = {
  .d_a = 19,  //set digital tube a-segment to pin 19
  .d_b = 17,
  .d_c = 14,
  .d_d = 13,
  .d_e = 5,
  .d_f = 23,
  .d_g = 27,
  .d_dp = 12,

  .G1 = 18,  //set digital tube group G1 to pin 18
  .G2 = 26,
  .G3 = 25,
  .G4 = 16,
};
//create SevenSegment object instance, and import the digital tube pin configuration into the internal code
DigitalTube digitalTube(myPins);

int val = 0;  //declare a val variable

void setup() {
}

void loop() {
  //Start counting from 0, gradually increase by 1 to 9999, and repeat.
  digitalTube.DisplayNum(val);
  if (millis() % 1000 < 5) {   //add 1 to val every second
    val = (val + 1);
    delay(6);
  }
}
