//master code, sends alert to slave to print

#include <Wire.h>
#include "Adafruit_VL53L0X.h"

// Distance Sensors
Adafruit_VL53L0X lox1 = Adafruit_VL53L0X();
Adafruit_VL53L0X lox2 = Adafruit_VL53L0X();

#define XSHUT1 24
#define XSHUT2 22

void setup() {
  Serial.begin(9600);
  Wire.begin(); // Master I2C

  pinMode(XSHUT1, OUTPUT);
  pinMode(XSHUT2, OUTPUT);

  // Disable both sensors first
  digitalWrite(XSHUT1, LOW);
  digitalWrite(XSHUT2, LOW);
  delay(10);

  // Initialize sensor 1
  digitalWrite(XSHUT1, HIGH);
  delay(10);
  if (!lox1.begin(0x30)) {
    Serial.println(F("Failed to boot first VL53L0X"));
    while (1);
  }

  // Initialize sensor 2
  digitalWrite(XSHUT2, HIGH);
  delay(10);
  if (!lox2.begin(0x31)) {
    Serial.println(F("Failed to boot second VL53L0X"));
    while (1);
  }

  Serial.println("VL53L0X sensors ready.");
}

void loop() {
  VL53L0X_RangingMeasurementData_t measure1, measure2;
  lox1.rangingTest(&measure1, false);
  lox2.rangingTest(&measure2, false);

  bool alert = false;

  if (measure1.RangeStatus != 4 && measure1.RangeMilliMeter <= 50) {
    Serial.println("Object detected by Sensor 1 within 5 cm!");
    alert = true;
  }

  if (measure2.RangeStatus != 4 && measure2.RangeMilliMeter <= 50) {
    Serial.println("Object detected by Sensor 2 within 5 cm!");
    alert = true;
  }

  if (alert) {
    Wire.beginTransmission(12);             // Uno slave address = 12
    Wire.write("ALERT");                    // Send message as text
    Wire.endTransmission();
    Serial.println("Sent ALERT to Slave.");
    delay(1000);                            // Simple debounce to avoid spamming
  }

  delay(100);  // Small delay for stability
}
