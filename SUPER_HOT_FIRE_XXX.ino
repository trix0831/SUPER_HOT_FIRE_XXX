#include <SPI.h>
#include <MFRC522.h>
#include "RFID.h"
#include <string.h>
#include "straight_turn.h"

#define maxn 1000
#define RST_PIN 9
#define SS_PIN 53

// MFRC522 *mfrc522;

#define PWMA 11
#define AIN2 3
#define AIN1 2
#define BIN1 5
#define BIN2 6
#define PWMB 12

#define speed 255

char val;
char val2 = 'o';
byte testid;
int stage = 0;
int lastState;
int started = 0;
int teststage = 0;

char orders[maxn]={'f','r','f','r','s'};

void motorWriting(int, int);

void setup() {

  // put your setup code here, to run once:
  Serial.begin (9600);
  Serial.println("serial ready");
  Serial1.begin(9600);
  Serial1.println("BT ready");
  pinMode(13, OUTPUT);

  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(PWMA, OUTPUT);
  pinMode(PWMB, OUTPUT);

  // RFID
  SPI.begin();
  mfrc522 = new MFRC522(SS_PIN, RST_PIN);
  // 請系統去要一塊記憶體空間，後面呼叫它的建構函式
  // 將(SS, RST) 當成參數傳進去初始化。
  mfrc522->PCD_Init();
  /* 初始化MFRC522讀卡機 PCD_Init 模組。 -> 表示：
  透過記憶體位置，找到 mfrc522 這物件，再翻其內容。*/
  Serial.println(F("Read UID on a MIFARE PICC:"));
}

void loop() {
  // put your main code here, to run repeatedly:
  analogWrite(PWMA, speed);
  analogWrite(PWMB, speed);

  // while(true){
  //   motorWriting(speed*7/8,speed);
  // }

  if (Serial.available()) {
    val = Serial.read();
    Serial1.println(val);
  }


  if (Serial1.available()) {
    val2 = Serial1.read();
    Serial.println(val2);
  }

  // while(started == 0){
  //   motorWriting(0,0);
  //   if (Serial1.available()) {
  //     val2 = Serial1.read();
  //     Serial.println(val2);
  //   }
  //   if (val2 == 'w'){
  //     break;
  //   }
  // }

  started = 0;

  // if(val2 == 'w'){
  //   motorWriting(speed, speed);
  // }else if(val2 == 's'){
  //   motorWriting(-speed, -speed);
  // }else if(val2 == 'a'){
  //   motorWriting(0, speed);
  // }else if(val2 == 'd'){
  //   motorWriting(speed, 0);
  // }else 

  // if(val2 == 'p'){
  //   while(Serial1.read() != 'w'){
  //     motorWriting(0,0);
  //   }
  // }

  Serial1.println("I'm here");
  rfid(testid);

  straight(&stage, &lastState);
  // Serial1.println(checkState(&stage, &lastState));
  if (checkState(&stage,&lastState) == 11111){
    if (orders[stage] == 'f'){
      Forward(&stage, &lastState);
    }else if (orders[stage] == 'l'){
      LeftTurn(&stage, &lastState);
    }else if (orders[stage] == 'r'){
      RightTurn(&stage, &lastState);
    }else if (orders[stage] == 'b'){
      UTurn(&stage, &lastState);
    }else{
      while(true){
        motorWriting(0,0);
      }
    }
  }

}


