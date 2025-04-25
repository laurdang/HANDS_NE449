#include <Wire.h>
#include "Adafruit_VL53L0X.h"
#include <SPI.h>
#include <MFRC522.h>
#include "Pill.h"

// Distance Sensors
Adafruit_VL53L0X lox1 = Adafruit_VL53L0X();
Adafruit_VL53L0X lox2 = Adafruit_VL53L0X();

#define XSHUT1 24
#define XSHUT2 22

#define MOTOR1_PIN 9
#define MOTOR2_PIN 10

int d1 = 0;
int d2 = 0;

// RFID
#define RST_PIN 5
#define SS_PIN 53
MFRC522 mfrc522(SS_PIN, RST_PIN);

unsigned long lastSendTime = 0;
const unsigned long cooldown = 3000;

void setup() {
  Serial.begin(9600);
  Wire.begin(); // I2C Master

  pinMode(XSHUT1, OUTPUT);
  pinMode(XSHUT2, OUTPUT);
  pinMode(MOTOR1_PIN, OUTPUT);
  pinMode(MOTOR2_PIN, OUTPUT);

  // Distance Sensor Initialization
  digitalWrite(XSHUT1, LOW);
  digitalWrite(XSHUT2, LOW);
  delay(10);

  digitalWrite(XSHUT1, HIGH);
  delay(10);
  if (!lox1.begin(0x30)) {
    Serial.println(F("Failed to boot first VL53L0X"));
    while (1);
  }

  digitalWrite(XSHUT2, HIGH);
  delay(10);
  if (!lox2.begin(0x31)) {
    Serial.println(F("Failed to boot second VL53L0X"));
    while (1);
  }

  Serial.println("VL53L0X sensors ready.");

  // RFID setup
  SPI.begin();
  mfrc522.PCD_Init();
  Serial.println("RFID initialized.");


}

void loop() {
  VL53L0X_RangingMeasurementData_t measure1, measure2;
  lox1.rangingTest(&measure1, false);
  lox2.rangingTest(&measure2, false);

  if (measure1.RangeStatus != 4) {
    d1 = measure1.RangeMilliMeter;
    Serial.print("Distance 1 (mm): ");
    Serial.println(d1);
    analogWrite(MOTOR1_PIN, constrain(map(d1, 300, 10, 0, 255), 0, 255));
  } else {
    analogWrite(MOTOR1_PIN, 0);
  }

  if (measure2.RangeStatus != 4) {
    d2 = measure2.RangeMilliMeter;
    Serial.print("Distance 2 (mm): ");
    Serial.println(d2);
    analogWrite(MOTOR2_PIN, constrain(map(d2, 300, 10, 0, 255), 0, 255));
  } else {
    analogWrite(MOTOR2_PIN, 0);
  }

  // RFID trigger condition
  if ((d1 < 100 || d2 < 100) && (millis() - lastSendTime > cooldown)) {
    if (!mfrc522.PICC_IsNewCardPresent()) return;
    if (!mfrc522.PICC_ReadCardSerial()) return;

    unsigned long tagID = 0;
    for (byte i = 0; i < mfrc522.uid.size; i++) {
      tagID = (tagID << 8) | mfrc522.uid.uidByte[i];
    }

    Serial.print("Tag ID: ");
    Serial.println(tagID);

    // Send tag ID to slave Arduino
    Wire.beginTransmission(12); // Slave I2C address
    for (int i = 3; i >= 0; i--) {
      Wire.write((tagID >> (8 * i)) & 0xFF); // Send each byte MSB first
    }
    Wire.endTransmission();

    lastSendTime = millis();
  }

  delay(1000);
}
