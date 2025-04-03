#ifndef DISPLAY_H
#define DISPLAY_H

#include "Arduino.h"

struct displayPins {
  const int d_a;  //定义数码管a段到引脚19
  const int d_b;
  const int d_c;
  const int d_d;
  const int d_e;
  const int d_f;
  const int d_g;
  const int d_dp;

  const int G1;  //定义数码管第一组G1到引脚18
  const int G2;
  const int G3;
  const int G4;
};

class DigitalTube {
public:

  DigitalTube(const displayPins& pins)
    : _pins(pins) {
    pinMode(_pins.d_a, OUTPUT);  //设置引脚d_a为输出引脚
    pinMode(_pins.d_b, OUTPUT);
    pinMode(_pins.d_c, OUTPUT);
    pinMode(_pins.d_d, OUTPUT);
    pinMode(_pins.d_e, OUTPUT);
    pinMode(_pins.d_f, OUTPUT);
    pinMode(_pins.d_g, OUTPUT);
    pinMode(_pins.d_dp, OUTPUT);

    pinMode(_pins.G1, OUTPUT);
    pinMode(_pins.G2, OUTPUT);
    pinMode(_pins.G3, OUTPUT);
    pinMode(_pins.G4, OUTPUT);
  }

  //显示功能:g的范围为1 ~ 4,num的范围为0 ~ 9
  void Display(unsigned char g, unsigned char n) {
    digitalWrite(_pins.d_a, LOW);  //
    digitalWrite(_pins.d_b, LOW);
    digitalWrite(_pins.d_c, LOW);
    digitalWrite(_pins.d_d, LOW);
    digitalWrite(_pins.d_e, LOW);
    digitalWrite(_pins.d_f, LOW);
    digitalWrite(_pins.d_g, LOW);
    digitalWrite(_pins.d_dp, LOW);

    switch (g)  //做出选择
    {
      case 1:
        digitalWrite(_pins.G1, LOW);  //选择第一个位
        digitalWrite(_pins.G2, HIGH);
        digitalWrite(_pins.G3, HIGH);
        digitalWrite(_pins.G4, HIGH);
        break;
      case 2:
        digitalWrite(_pins.G1, HIGH);
        digitalWrite(_pins.G2, LOW);  //选择第二个位
        digitalWrite(_pins.G3, HIGH);
        digitalWrite(_pins.G4, HIGH);
        break;
      case 3:
        digitalWrite(_pins.G1, HIGH);
        digitalWrite(_pins.G2, HIGH);
        digitalWrite(_pins.G3, LOW);  //选择第三个位
        digitalWrite(_pins.G4, HIGH);
        break;
      case 4:
        digitalWrite(_pins.G1, HIGH);
        digitalWrite(_pins.G2, HIGH);
        digitalWrite(_pins.G3, HIGH);
        digitalWrite(_pins.G4, LOW);  //选择第四个位
        break;
      default: break;
    }

    digitalWrite(_pins.d_a, num[n][0]);  //a查询码值表
    digitalWrite(_pins.d_b, num[n][1]);
    digitalWrite(_pins.d_c, num[n][2]);
    digitalWrite(_pins.d_d, num[n][3]);
    digitalWrite(_pins.d_e, num[n][4]);
    digitalWrite(_pins.d_f, num[n][5]);
    digitalWrite(_pins.d_g, num[n][6]);
    digitalWrite(_pins.d_dp, num[n][7]);
  }

  void DisplayNum(int num) {
    int value[4];
    if (num >= 0 && num <= 9999) {  //判断输入的数在0-9999范围内
      value[0] = num / 1000;        //提取出千位数
      value[1] = (num / 100) % 10;  //提取出百位数
      value[2] = (num / 10) % 10;   //提取出十位数
      value[3] = num % 10;          //提取出个位数
      for (int i = 0; i < 4; i++) {
        Display(i + 1, value[i]);
      }
    } else {  //大于9999以及小于0的数直接全部显示0
      for (int i = 0; i < 4; i++) {
        Display(i + 1, 0);
      }
    }
  }

private:

  displayPins _pins;  // 存储配置参数
  //数码管0-F码值
  unsigned char num[17][8] = {
    //a  b  c  d  e  f  g  dp
    { 1, 1, 1, 1, 1, 1, 0, 0 },  //0
    { 0, 1, 1, 0, 0, 0, 0, 0 },  //1
    { 1, 1, 0, 1, 1, 0, 1, 0 },  //2
    { 1, 1, 1, 1, 0, 0, 1, 0 },  //3
    { 0, 1, 1, 0, 0, 1, 1, 0 },  //4
    { 1, 0, 1, 1, 0, 1, 1, 0 },  //5
    { 1, 0, 1, 1, 1, 1, 1, 0 },  //6
    { 1, 1, 1, 0, 0, 0, 0, 0 },  //7
    { 1, 1, 1, 1, 1, 1, 1, 0 },  //8
    { 1, 1, 1, 1, 0, 1, 1, 0 },  //9
    { 1, 1, 1, 0, 1, 1, 1, 1 },  //A
    { 1, 1, 1, 1, 1, 1, 1, 1 },  //B
    { 1, 0, 0, 1, 1, 1, 0, 1 },  //C
    { 1, 1, 1, 1, 1, 1, 0, 1 },  //D
    { 1, 0, 0, 1, 1, 1, 1, 1 },  //E
    { 1, 0, 0, 0, 1, 1, 1, 1 },  //F
    { 0, 0, 0, 0, 0, 0, 0, 1 },  //.
  };
};


#endif