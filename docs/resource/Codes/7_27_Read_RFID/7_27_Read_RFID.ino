/*  
 * 名称   : 7_27_Read_RFID
 * 功能   : 读取RFID卡值
 * 编译IDE：ARDUINO 2.3.4
 * 作者   : https://www.keyestudio.com/
*/
#include <MFRC522.h>  // 引入MFRC522库，用于控制MFRC522 RFID模块

// 定义RFID模块的引脚
#define SS_PIN  5   // SPI的片选引脚（SS），用于选择RFID模块
#define RST_PIN 13  // 复位引脚，用于重置RFID模块

// 创建MFRC522对象，传入SS引脚和复位引脚
MFRC522 mfrc522(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(9600);  // 初始化串口通信，设置波特率为9600，用于调试输出
  SPI.begin();           // 初始化SPI通信，配置与MFRC522的SPI接口
  mfrc522.PCD_Init();    // 初始化MFRC522 RFID模块，设置SPI通信参数
  Serial.println("RFID Reader Initialized. Place your card near the reader...");  // 提示用户放置RFID卡片
}

void loop() {
  // 检查是否有新的RFID卡靠近并准备读取
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    // 如果卡片被检测到并且成功读取卡片序列号（UID）
    Serial.print("Card UID: ");  // 打印“Card UID:”信息
    for (byte i = 0; i < mfrc522.uid.size; i++) {
      // 循环遍历卡片UID的每个字节
      Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");  // 如果字节小于0x10，加前导零，确保输出格式一致
      Serial.print(mfrc522.uid.uidByte[i], HEX);  // 以十六进制打印每个字节
    }
    Serial.println();  // 换行，结束UID输出

    // 停止与当前卡片的通信，释放SPI总线
    mfrc522.PICC_HaltA();
  }
}
