/*
 * Filename   : 7_15_8x8-Matrix_Display
 * Function   : 8x8 dot matrix shows 1-9, heart, smile and crying face
 * Compiling IDE: ARDUINO 2.3.4
 * Function： Matrix.DisplayNum(num) is used to display numbers. When used, change num to a number 0-9 to display the corresponding number
   Matrix.DisplayImage("str"); displays the pattern, when used, enter the string "heart" or "smile" or "cry" to display the corresponding pattern
 * Author: https://www.keyestudio.com/ 
*/
#include "matrix.h"
//set matrix pins
const MatrixPins myPins = {
  .ROW = { 18, 19, 23, 5, 13, 12, 14, 27 },
  .COLUMN = { 16, 17, 25, 26, 33, 32, 4, 2 }
};
//Create an instance of the matrix class and import the control pin configuration into the internal code
matrix Matrix(myPins);

void setup() {
}

void loop() {
  Matrix.DisplayNum(0); //show number "0"
  Matrix.DisplayNum(1); //show number "1"
  Matrix.DisplayNum(2); //show number "2"
  Matrix.DisplayNum(3); 
  Matrix.DisplayNum(4);
  Matrix.DisplayNum(5);
  Matrix.DisplayNum(6);
  Matrix.DisplayNum(7);
  Matrix.DisplayNum(8);
  Matrix.DisplayNum(9); //show number "9"

  Matrix.DisplayImage("heart");  //show heart icon
  Matrix.DisplayImage("smile"); //show smile icon
  Matrix.DisplayImage("cry"); //show cry icon
}
