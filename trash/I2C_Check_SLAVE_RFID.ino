#include <Wire.h>
#include <WaveHC.h>
#include <WaveUtil.h>
#include "Pill.h"

#define SLAVE_ADDRESS 12
#define SD_CS 10

SdReader card;
FatVolume vol;
FatReader root;
FatReader file;
WaveHC wave;

void setup() {
  Serial.begin(9600);

  pinMode(SD_CS, OUTPUT);
  digitalWrite(SD_CS, HIGH);

  Wire.begin(SLAVE_ADDRESS);
  Wire.onReceive(receiveEvent);

  Serial.println("UNO Slave with Wave Shield.");

  if (!card.init()) {
    Serial.println("SD card init failed!");
    return;
  }
  if (!vol.init(card)) {
    Serial.println("Volume init failed!");
    return;
  }
  if (!root.openRoot(vol)) {
    Serial.println("Opening root failed!");
    return;
  }
}

void loop() {
  // Nothing to do here
}

void receiveEvent(int howMany) {
  if (howMany != 4) {
    Serial.println("Incorrect byte count received.");
    return;
  }

  unsigned long receivedTagID = 0;
  while (Wire.available()) {
    receivedTagID = (receivedTagID << 8) | Wire.read();
  }

  Serial.print("Received Tag ID: ");
  Serial.println(receivedTagID, HEX);

  for (int i = 0; i < 2; i++) { // Adjusted to match pill array size
    if (pills[i].ID == receivedTagID) {
      pills[i].printInfo();
      playFile(pills[i].filename);  // Pass String directly
      break;
    }
  }
}

void playFile(const String &name) {
  if (wave.isplaying) wave.stop();

  char filename[name.length() + 1]; // Create a buffer to hold the filename
  name.toCharArray(filename, sizeof(filename)); // Copy the String to the char array

  if (!file.open(root, filename)) {  // Now pass a mutable char array
    Serial.print("Couldn't open file: ");
    Serial.println(filename);
    return;
  }

  if (!wave.create(file)) {
    Serial.println("Not a valid WAV file");
    return;
  }

  Serial.print("Playing: ");
  Serial.println(filename);
  wave.play();

  while (wave.isplaying) {
    // Wait while playing
  }
}
