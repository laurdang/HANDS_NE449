#include "Pill.h"

Pill::Pill() {
  ID = 0;
  name = "default";
  filename = "DEFAULT";
}

Pill::Pill(unsigned long ID, String name, String filename) {
  this->ID = ID;
  this->name = name;
  this->filename = filename;
}

void Pill::printInfo() {
  Serial.println();
  Serial.println("Pill Info:");
  Serial.print("Name: ");
  Serial.println(name);
  Serial.print("Filename: ");
  Serial.println(filename);
}

Pill pills[] = {
  // Names and number of objects are condensed to conserve memory
  Pill(3135019583, "ATO", "3.WAV"), // Atorvastatin
  Pill(1792842303, "XAN", "4.WAV"), // Xanax
  Pill(2061277759, "VIA", "5.WAV"), // Viagra

  // Other example objects (some are not pills):
  // Pill(3403455039, "CAY", "1.WAV"), // Cayenne pepper
  // Pill(3671890495, "OXY", "2.WAV"), // Oxycodon
  // Pill(2598148671, "TUM", "6.WAV"), // Tumeric
  // Pill(2866584127, "ITA", "7.WAV"), // Italian seasoning
  // Pill(2329713215, "TYE", "8.WAV"), // Tyelenol
};
