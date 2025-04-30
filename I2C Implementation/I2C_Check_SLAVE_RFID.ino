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

  // Set up SD card
  pinMode(SD_CS, OUTPUT);
  digitalWrite(SD_CS, HIGH);

  // Set up slave to recieve event
  Wire.begin(SLAVE_ADDRESS);
  Wire.onReceive(receiveEvent);

  Serial.println("UNO Slave with Wave Shield.");

  // Wave shield initiations
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

  Serial.println("all set");
}

void loop() {
  // Nothing to do here
}

void receiveEvent(int howMany) {
  // Checking if correct number of bytes sent by master
  if (howMany != 4) {
    Serial.println("Incorrect byte count received.");
    return;
  }

  unsigned long receivedTagID = 0;
  while (Wire.available()) {
    receivedTagID = (receivedTagID << 8) | Wire.read(); // Recieving bytes from master
  }

  Serial.print("Received Tag ID: ");
  Serial.println(receivedTagID);

  for (int k = 0; k < 3; k++) { // Iterate through Pill object array, can adjust to match pill array size
    if (pills[k].ID == receivedTagID) { // Play associated file if recieved tag matches tag of a Pill object
      Serial.println("match");
      Serial.println(pills[k].filename);
      playFile(pills[k].filename);
    }
  }
}

void playFile(String filename) {
  char charArray[6];  // Stores char array version of filename
  filename.toCharArray(charArray, sizeof(charArray)); // Converts filename to char array
  Serial.println(charArray);
  
  // Open the file from the root
  if (!file.open(root, charArray)) {
    Serial.print("Couldn't open file: ");
    Serial.println(charArray);
    return;
  }
  
  // Prepare the wave object
  if (!wave.create(file)) {
    Serial.println("Couldn't create wave");
    return;
  }

  // Play the sound
  wave.play();
}