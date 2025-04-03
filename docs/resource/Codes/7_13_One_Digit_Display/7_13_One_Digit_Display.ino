/*
 * Filename   : 7_13_One_Digit_Display
 * Function   : 1-bit digital tube shows number 0-9
 * Compiling IDE: ARDUINO 2.3.4
 * Author: https://www.keyestudio.com/
*/
const int rckPin = 23;  //RCK
const int sckPin = 18;  //SCK
const int siPin = 5;    //SI
//Store the numeric segment code in an array
int datArray[] = { 0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f };

void setup() {
  //set pins to output
  pinMode(rckPin, OUTPUT);
  pinMode(sckPin, OUTPUT);
  pinMode(siPin, OUTPUT);
}

void loop() {
  for (int num = 0; num < 10; num++) {
    displayNum(num);
    delay(1000);
  }
}
/*
  function：displayNum
  It control the digital tube to show 0-9
            Put the number you want to display in parentheses around the function
            if you want to show 1，"displayNum(1);"
*/
void displayNum(int num) {
  digitalWrite(rckPin, LOW);  //ground RCK and hold low for as long as you are transmitting
  shiftOut(siPin, sckPin, MSBFIRST, datArray[num]);
  digitalWrite(rckPin, HIGH);  //pull the RCK to save the data
}