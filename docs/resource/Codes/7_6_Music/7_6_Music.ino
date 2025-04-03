/*
 * Filename   : 7_6_Music
 * Function   : passive buzzer plays a birthday song
 * Compiling IDE: ARDUINO 2.3.4
 * Author: https://www.keyestudio.com/
*/
int beeppin = 13;  //set buzzer to pin IO5
// do、re、mi、fa、so、la、si
int doremi[] = { 262, 294, 330, 370, 392, 440, 494,                                                        //Flat 0-6
                 523, 587, 659, 698, 784, 880, 988,                                                        //Natural 7-13
                 1047, 1175, 1319, 1397, 1568, 1760, 1967 };                                               //Sharp 14-20
int happybirthday[] = { 5, 5, 6, 5, 8, 7, 5, 5, 6, 5, 9, 8, 5, 5, 12, 10, 8, 7, 6, 11, 11, 10, 8, 9, 8 };  // Locate the position number in the doremi[] array based on the note
int meter[] = { 1, 1, 2, 2, 2, 4, 1, 1, 2, 2, 2, 4, 1, 1, 2, 2, 2, 2, 2, 1, 1, 2, 2, 2, 4 };               // beat

void setup() {
  pinMode(beeppin, OUTPUT);  //set IO5 to output
}

void loop() {
  for (int i = 0; i <= 24; i++) {                 //i<=24 because there are only 24 keys in the note
    tone(beeppin, doremi[happybirthday[i] - 1]);  //tone() function emits a waveform with frequency "frequency"
    delay(meter[i] * 200);                        //delay 1000ms
    noTone(beeppin);                              //stop
  }
}
