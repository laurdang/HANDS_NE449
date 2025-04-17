#ifndef PILL_H
#define PILL_H

#include <Arduino.h>  // ← absolutely required for String!

class Pill {
  public:
    unsigned long ID;
    String IDlabel;
    String name;
    String type;
    String dosage;
    String instructions;

    Pill();
    Pill(unsigned long ID, String IDlabel, String name, String type, String dosage, String instructions);
    void printInfo();
};

extern Pill pills[];

#endif
