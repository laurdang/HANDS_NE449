#include "Pill.h"

Pill::Pill() {
  ID = 0;
  IDlabel = "default";
  filename = "default";
}

Pill::Pill(unsigned long ID,String IDlabel, String filename) {
  this->ID = ID;
  this->IDlabel = IDlabel;
  this->filename = filename;
}

void Pill::printInfo() {
  Serial.println();
  Serial.println("Pill Info:");
  Serial.print("ID (label): "); Serial.println(IDlabel);
  Serial.print("Filename: "); Serial.println(filename);
}

Pill pills[2] = {
  Pill(0xCADC9A3F, "CADC9A3F", "Cayenne.wav"),
  Pill(0xDADC9A3F, "DADC9A3F", "Oxycodon.wav"),
  Pill(0xBADC9A3F, "BADC9A3F", "Atorvastatin.wav"),
  Pill(0xAADC9A3F, "AADC9A3F", "Italian Seasoning.wav"),
};
