#ifndef PILL_H
#define PILL_H

#include <Arduino.h>  // ← absolutely required for String!

class Pill {
  public:
    unsigned long ID;
    String IDlabel;
    String filename;
    

    Pill();
    Pill(unsigned long ID, String IDlabel, String filename);
    void printInfo();
};

extern Pill pills[];

#endif
