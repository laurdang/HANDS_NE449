#include "Pill.h"

Pill::Pill() {
  ID = 0;
  IDlabel = "default";
  filename = "DEFAULT";
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

Pill pills[] = {
  Pill(0xCADC9A3F, "CADC9A3F", "CAYENNE_PEPPER.WAV"),
  Pill(0xDADC9A3F, "DADC9A3F", "OXYCODON.WAV"),
  Pill(0xAADC9A3F, "AADC9A3F", "ATORVASTATIN.WAV"),
  Pill(0x6ADC9A3F, "6ADC9A3F", "XANAX.WAV"),
  Pill(0x7ADC9A3F, "7ADC9A3F", "VIAGRA.WAV"),
};
