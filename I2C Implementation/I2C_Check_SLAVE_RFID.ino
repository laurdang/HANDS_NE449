
#include <Wire.h>

#define SLAVE_ADDRESS 12      // Make sure this matches your Mega code
#define SD_CS 10              // Wave Shield's CS pin
#define LED_PIN 13            // Optional: LED to confirm communication

void setup() {
  Serial.begin(9600);

  // Disable Wave Shield (keep SD card inactive)
  pinMode(SD_CS, OUTPUT);
  digitalWrite(SD_CS, HIGH);   // Deselect SD card, prevent SPI from interfering

  Wire.begin(SLAVE_ADDRESS);   // Initialize I2C as slave at address 12
  Wire.onReceive(receiveEvent); // Attach receive event handler

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);   // Start with LED off

  Serial.println("UNO Slave ready with Wave Shield attached.");
}

void loop() {
  // Nothing needed here; waiting for I2C receive interrupts
}

void receiveEvent(int howMany) {
  if (howMany != 4) {              // Expect exactly 4 bytes for tag ID
    Serial.println("Incorrect byte count received.");
    return;
  }

  unsigned long receivedTagID = 0;               // Reset tagID before reassembling

  while (Wire.available()) {
    receivedTagID = (receivedTagID << 8) | Wire.read();  // Reassemble MSB first
  }

  Serial.print("Received Tag ID: ");
  Serial.println(receivedTagID);

// ==== TO DO: PLAY FILE (comment out this section to test if it is reading the RFID) ======
  for (int ii = 0; ii < 4; ii++)){ // searching through array of pills
    if (pills[ii].ID == receivedTagID){ // if the ID of pill matches RFID
      // play pills[ii].filename
    }
  }
}


