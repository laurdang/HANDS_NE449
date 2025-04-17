#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN 9
#define SS_PIN 10
#include "Pill.h"

MFRC522 mfrc522(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(9600);
  SPI.begin(); 
  mfrc522.PCD_Init();
  Serial.println("Scan a card...");
}

void loop() {
  if ( ! mfrc522.PICC_IsNewCardPresent()) return;
  if ( ! mfrc522.PICC_ReadCardSerial()) return;

  // READ ID AND CONVERT ID INTO INT
  unsigned long tagID = 0;
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    tagID = (tagID << 8) | mfrc522.uid.uidByte[i];  // shift and add
  }

  // CHECK ID WITH STORED ID AND PRINT INFO
  int ii = 0;
  while (ii < 2){
    if (pills[ii].ID == tagID){
      pills[ii].printInfo();
      delay(1000);
    }
    ii++;
  }
  
}
