// master code, sends alert to slave to play audio file


#include <Wire.h> // Library for I2C connection
#include "Adafruit_VL53L0X.h" // Library for sensors
#include <SPI.h> // Library that allows RFID Reader communication
#include <MFRC522.h> // Library for RFID module
#include "Pill.h" // Header file containing RFID tags


// Distance Sensors
Adafruit_VL53L0X lox1 = Adafruit_VL53L0X();
Adafruit_VL53L0X lox2 = Adafruit_VL53L0X();


#define XSHUT1 24
#define XSHUT2 22


#define MOTOR1_PIN 13 // Motor 1 pin
#define MOTOR2_PIN 2  // Motor 2 pin


int d1 = 0; // Record distance of sensor 1
int d2 = 0; // Record distance of sensor 2


// RFID
#define RST_PIN 5
#define SS_PIN 53
MFRC522 mfrc522(SS_PIN, RST_PIN); // Pin set-up for RFID


unsigned long lastSendTime = 0;
const unsigned long cooldown = 3000;


void setup() {
 Serial.begin(9600);
 Wire.begin(); // Master I2C


 pinMode(XSHUT1, OUTPUT);
 pinMode(XSHUT2, OUTPUT);
 pinMode(MOTOR1_PIN, OUTPUT);
 pinMode(MOTOR2_PIN, OUTPUT);


 // Disable both sensors first
 digitalWrite(XSHUT1, LOW);
 digitalWrite(XSHUT2, LOW);
 delay(10);


 // Initialize sensor 1
 digitalWrite(XSHUT1, HIGH);
 delay(10);
 if (!lox1.begin(0x30)) {
   Serial.println(F("Failed to boot first VL53L0X"));
   while (1); // Stop, something's wrong with sensor 1
 }


 // Initialize sensor 2
 digitalWrite(XSHUT2, HIGH);
 delay(10);
 if (!lox2.begin(0x31)) {
   Serial.println(F("Failed to boot second VL53L0X"));
   while (1); // Stop, something's wrong with sensor 2
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


 if (measure1.RangeStatus != 4) {  // If no error (status 4 = out of range or failed)
   d1 = measure1.RangeMilliMeter;
   Serial.print("Distance 1 (mm): ");
   Serial.println(d1); // Print distance calculated by sensor 1
   analogWrite(MOTOR1_PIN, constrain(map(d1, 300, 10, 0, 255), 0, 255));
 } else {
   analogWrite(MOTOR1_PIN, 0);
 }


 if (measure2.RangeStatus != 4) {
   d2 = measure2.RangeMilliMeter;
   Serial.print("Distance 2 (mm): ");
   Serial.println(d2); // Print distance calculated by sensor 2
   analogWrite(MOTOR2_PIN, constrain(map(d2, 300, 10, 0, 255), 0, 255));
 } else {
   analogWrite(MOTOR2_PIN, 0);
 }


 // RFID trigger condition
 if ((d1 < 80 || d2 < 80) && (millis() - lastSendTime > cooldown)) { // If the distance of an object from both sensors is less than 80 mm 
   if (!mfrc522.PICC_IsNewCardPresent()) return; // If RFID is not detected
   if (!mfrc522.PICC_ReadCardSerial()) return; // If failed to read, return 


   unsigned long tagID = 0;
   for (byte i = 0; i < mfrc522.uid.size; i++) {
     tagID = (tagID << 8) | mfrc522.uid.uidByte[i];
   }


   Serial.print("Tag ID: ");
   Serial.println(tagID);
   Wire.beginTransmission(12);             // Uno slave address = 12
   for (int i = 3; i >= 0; i--) {
     Wire.write((tagID >> (8 * i)) & 0xFF); // Send each byte MSB first
   }
   Wire.endTransmission();
   Serial.println("Sent Tag to Slave.");
   delay(1000);                            // Simple debounce to avoid spamming
 }
 delay(100);  // Small delay for stability
}

