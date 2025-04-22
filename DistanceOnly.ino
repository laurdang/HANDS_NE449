#include <Wire.h>
#include "Adafruit_VL53L0X.h"


// Sensor objects
Adafruit_VL53L0X lox1 = Adafruit_VL53L0X();
Adafruit_VL53L0X lox2 = Adafruit_VL53L0X();


// XSHUT control pins
#define XSHUT1 22
#define XSHUT2 24


// Motor PWM pins
#define MOTOR1_PIN 9
#define MOTOR2_PIN 11


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
  delay(5);
  if (!lox1.begin(0x30)) {
    Serial.println(F("Failed to boot first VL53L0X"));
    while (1)
      ;
  }


  // Turn on second sensor
  digitalWrite(XSHUT2, HIGH);
  delay(10);
  if (!lox2.begin(0x31)) {
    Serial.println(F("Failed to boot second VL53L0X"));
    while (1)
      ;
  }


  Serial.println("Both VL53L0X sensors initialized.");
}


void loop() {
  VL53L0X_RangingMeasurementData_t measure1;
  VL53L0X_RangingMeasurementData_t measure2;


  lox1.rangingTest(&measure1, false);
  lox2.rangingTest(&measure2, false);


  // === Sensor 1 → Motor 1 ===
  if (measure1.RangeStatus != 4) {
    int d1 = measure1.RangeMilliMeter;
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
    int d2 = measure2.RangeMilliMeter;
    Serial.print("Distance 2 (mm): ");
    Serial.println(d2);
    int strength2 = map(d2, 300, 10, 0, 255);
    strength2 = constrain(strength2, 0, 255);
    analogWrite(MOTOR2_PIN, strength2);
  } else {
    Serial.println("Sensor 2 out of range");
    analogWrite(MOTOR2_PIN, 0);
  }


  delay(100);  // Small delay to stabilize readings
}
