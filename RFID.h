/***************************************************************************/
// File       [RFID.h]
// Author     [Erik Kuo]
// Synopsis   [Code for getting UID from RFID card]
// Functions  [rfid]
// Modify     [2020/03/27 Erik Kuo]
/***************************************************************************/

#ifndef RFID_H
#define RFID_H
/*===========================don't change anything in this file===========================*/

#include <SPI.h>
#include <MFRC522.h>     // 引用程式庫
/* pin---- SDA:9 SCK:13 MOSI:11 MISO:12 GND:GND RST:define on your own  */

MFRC522 *mfrc522;

byte* rfid(byte& idSize) {
    int tmp = 0;

    // 確認是否有新卡片
    if (mfrc522->PICC_IsNewCardPresent() && mfrc522->PICC_ReadCardSerial()) {
      byte *id = mfrc522->uid.uidByte;   // 取得卡片的UID
      idSize = mfrc522->uid.size;   // 取得UID的長度

      //Serial.print("PICC type: ");      // 顯示卡片類型
      // 根據卡片回應的SAK值（mfrc522.uid.sak）判斷卡片類型
      //MFRC522::PICC_Type piccType = mfrc522.PICC_GetType(mfrc522.uid.sak);
      //Serial.println(mfrc522.PICC_GetTypeName(piccType));
      // #ifdef DEBUG
      // Serial1.print("UID Size: ");       // 顯示卡片的UID長度值
      // Serial1.println(idSize);   
      for (byte i = 0; i < idSize; i++) {  // 逐一顯示UID碼
        
        // Serial1.print(i);
        // Serial1.print("]: ");

        if(id[i] < 16){
          Serial1.print("0");
        }

        Serial1.print(id[i], HEX);       // 以16進位顯示UID值  
        // Serial1.print(" ");
      }
      Serial1.print("\n");
      // #endif
      mfrc522->PICC_HaltA();  // 讓卡片進入停止模式
      // Serial1.println(id);
      return id;
    }
    return 0;
}

#endif