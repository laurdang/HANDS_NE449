#include "Pill.h"

Pill::Pill() {
  ID = 0;
  IDlabel = "default";
  name = "default";
  type = "default";
  dosage = "default";
  instructions = "default";
}

Pill::Pill(unsigned long ID,String IDlabel, String name, String type, String dosage, String instructions) {
  this->ID = ID;
  this->IDlabel = IDlabel;
  this->name = name;
  this->type = type;
  this->dosage = dosage;
  this->instructions = instructions;
}

void Pill::printInfo() {
  Serial.println();
  Serial.println("Pill Info:");
  Serial.print("ID (label): "); Serial.println(IDlabel);
  Serial.print("Name: "); Serial.println(name);
  Serial.print("Type: "); Serial.println(type);
  Serial.print("Dosage: "); Serial.println(dosage);
  Serial.print("Instructions: "); Serial.println(instructions);
}

Pill pills[2] = {
  Pill(0xCADC9A3F, "CADC9A3F", "Cayenne", "NSAID", "200mg", "Take with food"),
  Pill(0xDADC9A3F, "DADC9A3F", "Oxy", "Antihistamine", "10mg", "Once daily")
};
