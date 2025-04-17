// DISTANCE SETUP
#include <Wire.h>
#include "Adafruit_VL53L0X.h"

// Sensor objects
Adafruit_VL53L0X lox1 = Adafruit_VL53L0X();
Adafruit_VL53L0X lox2 = Adafruit_VL53L0X();

// XSHUT control pins
#define XSHUT1 4
#define XSHUT2 2

// Motor PWM pins
#define MOTOR1_PIN 5
#define MOTOR2_PIN 6

// Distance variables
int d1 = 0;
int d2 = 0;


// RFID SETUP
#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN 9
#define SS_PIN 10
#include "Pill.h"

MFRC522 mfrc522(SS_PIN, RST_PIN);


void setup() {
 Serial.begin(9600);
 Wire.begin();


 pinMode(XSHUT1, OUTPUT);
 pinMode(XSHUT2, OUTPUT);
 pinMode(MOTOR1_PIN, OUTPUT);
 pinMode(MOTOR2_PIN, OUTPUT);


 // Turn off both sensors
 digitalWrite(XSHUT1, LOW);
 digitalWrite(XSHUT2, LOW);
 delay(10);


 // Turn on first sensor only
 digitalWrite(XSHUT1, HIGH);
 delay(10);
 if (!lox1.begin(0x30)) {
   Serial.println(F("Failed to boot first VL53L0X"));
   while (1);
 }


 // Turn on second sensor
 digitalWrite(XSHUT2, HIGH);
 delay(10);
 if (!lox2.begin(0x31)) {
   Serial.println(F("Failed to boot second VL53L0X"));
   while (1);
 }


 Serial.println("Both VL53L0X sensors initialized.");

  SPI.begin(); 
  mfrc522.PCD_Init();
  Serial.println("RFID set up");
}


void loop() {
 VL53L0X_RangingMeasurementData_t measure1;
 VL53L0X_RangingMeasurementData_t measure2;


 lox1.rangingTest(&measure1, false);
 lox2.rangingTest(&measure2, false);


 // === Sensor 1 → Motor 1 ===
 if (measure1.RangeStatus != 4) {
   d1 = measure1.RangeMilliMeter;
   Serial.print("Distance 1 (mm): ");
   Serial.println(d1);
   int strength1 = map(d1, 300, 10, 0, 255);
   strength1 = constrain(strength1, 0, 255);
   analogWrite(MOTOR1_PIN, strength1);
 } else {
   Serial.println("Sensor 1 out of range");
   analogWrite(MOTOR1_PIN, 0);
 }


 // === Sensor 2 → Motor 2 ===
 if (measure2.RangeStatus != 4) {
   d2 = measure2.RangeMilliMeter;
   Serial.print("Distance 2 (mm): ");
   Serial.println(d2);
   int strength2 = map(d2, 300, 10, 0, 255);
   strength2 = constrain(strength2, 0, 255);
   analogWrite(MOTOR2_PIN, strength2);
 } else {
   Serial.println("Sensor 2 out of range");
   analogWrite(MOTOR2_PIN, 0);
 }



 // == TRIGGER RFID ==
 if (d1 < 100 || d2 < 100 ){
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

 delay(100); // Small delay to stabilize readings
}
