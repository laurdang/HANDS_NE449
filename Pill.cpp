#include "Pill.h"

Pill::Pill() {
  ID = 0;
  IDlabel = "default";
  filename = "DEFAULT";
}

Pill::Pill(unsigned long ID, String IDlabel, String filename) {
  this->ID = ID;
  this->IDlabel = IDlabel;
  this->filename = filename;
}

void Pill::printInfo() {
  Serial.println();
  Serial.println("Pill Info:");
  Serial.print("ID (label): ");
  Serial.println(IDlabel);
  Serial.print("Name: ");
  Serial.println(filename);
}

Pill pills[] = {
  Pill(3135019583, "ato", "3.WAV"),
  Pill(1792842303, "xan", "4.WAV"),
  Pill(2061277759, "via", "5.WAV"),

  // Other example objects:
  // Pill(3403455039, "cay", "1.WAV"),
  // Pill(3671890495, "oxy", "2.WAV"),
  // Pill(2598148671, "tum", "6.WAV"),
  // Pill(2866584127, "ita", "7.WAV"),
  // Pill(2329713215, "tye", "8.WAV"),
};
