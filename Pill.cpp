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
  Serial.print("Name: "); Serial.println(filename);
}

Pill pills[2] = {
  Pill(0xCADC9A3F, "CADC9A3F", "Cayenne"),
  Pill(0xDADC9A3F, "DADC9A3F", "Oxy")
};
