/*  
 * Filename   : 7_26_OLED_Display
 * Function   : OLED shows “Hello!” in three sizes
 * Compiling IDE: ARDUINO 2.3.4
 * Author: https://www.keyestudio.com/
*/
#include <GyverOLED.h>  // Introduce GyverOLED library for controlling OLED display

GyverOLED<SSH1106_128x64> oled;  // Create an OLED object specifying the display model SSH1106 with a resolution of 128x64

void setup() {
  oled.init();   // initialize OLED
  oled.clear();  // Clear the screen, making sure it is initially blank
}

void loop() {

  oled.setScale(1);        // set size to 1
  oled.setCursorXY(0, 0);  // set character position
  oled.println("Hello!");  // show character
  oled.update();           // refresh

  oled.setScale(2);         // set size to 2
  oled.setCursorXY(0, 10);  // set character position
  oled.println("Hello!");   // show character
  oled.update();            // refresh

  oled.setScale(3);         // set size to 3 (large)
  oled.setCursorXY(0, 35);  // set character position
  oled.println("Hello!");   // show character
  oled.update();            // refresh
}
