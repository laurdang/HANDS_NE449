#ifndef PILL_H
#define PILL_H

#include <Arduino.h> 

class Pill {
  public: // initialise public fields
    unsigned long ID;
    String name;
    String filename;

    Pill();
    Pill(unsigned long ID, String name, String filename);
    void printInfo();
};

extern Pill pills[];

#endif
