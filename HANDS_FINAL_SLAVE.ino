#include <Wire.h>
#include <WaveHC.h>
#include <WaveUtil.h>
#include <SD.h>
#include "Pill.h"  // Include your Pill definitions

#define I2C_SLAVE_ADDR 9
#define SD_CS 10

SdReader card;
FatVolume volume;
FatReader root;
FatReader waveFile;
WaveHC wave;

char filename[20];  
unsigned long receivedTagID = 0;
bool hasNewTag = false;

void setup() {
  Serial.begin(9600);

  if (!card.init()) {
    Serial.println(F("SD card init failed!"));
    while (1);
  }
  if (!volume.init(card)) {
    Serial.println(F("Volume not found!"));
    while (1);
  }
  if (!root.openRoot(volume)) {
    Serial.println(F("Cannot open root directory!"));
    while (1);
  }

  Serial.println("Wave Shield ready.");
  Wire.begin(I2C_SLAVE_ADDR);
  Wire.onReceive(receiveEvent);
}

void loop() {
  if (hasNewTag) {
    Serial.print("Looking for file: ");
    Serial.println(filename);

    if (!wave.isplaying) {
      if (waveFile.open(root, filename)) {
        Serial.print(F("Playing file: "));
        Serial.println(filename);
        wave.play(*waveFile);
      } else {
        Serial.println(F("File not found. Playing fallback."));
        if (waveFile.open(root, "DEFAULT.WAV")) {
          wave.play(&waveFile);
        }
      }
    }

    hasNewTag = false;
  }
}

void receiveEvent(int howMany) {
  if (howMany != 4) return;

  receivedTagID = 0;
  for (int i = 0; i < 4; i++) {
    receivedTagID = (receivedTagID << 8) | Wire.read();
  }

  Serial.print("Received tag ID over I2C: ");
  Serial.println(receivedTagID);

  // Search for matching ID in pills array
  bool found = false;
  for (int i = 0; i < NUM_PILLS; i++) {
    if (pills[i].ID == receivedTagID) {
      strncpy(filename, pills[i].filename, sizeof(filename));
      filename[sizeof(filename) - 1] = '\0';  // Null-terminate
      found = true;
      break;
    }
  }

  if (!found) {
    Serial.println(F("Tag ID not recognized, using DEFAULT.WAV"));
    strncpy(filename, "DEFAULT.WAV", sizeof(filename));
    filename[sizeof(filename) - 1] = '\0';
  }

  hasNewTag = true;
}
