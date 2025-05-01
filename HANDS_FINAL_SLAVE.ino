// slave code, receives ID and plays file

#include <Wire.h>
#include <WaveHC.h>
#include <WaveUtil.h>
#include "Pill.h"


#define SLAVE_ADDRESS 12
#define SD_CS 10
// Wave shield set-up
SdReader card; // SD Card reader
FatVolume vol; // FAT32 file system
FatReader root; // Root directory of SD card
FatReader file; // File to play
WaveHC wave; // WaveHC player


void setup() {
 Serial.begin(9600);


 // Set up SD card
 pinMode(SD_CS, OUTPUT);
 digitalWrite(SD_CS, HIGH);


 // Set up slave to recieve event
 Wire.begin(SLAVE_ADDRESS);
 Wire.onReceive(receiveEvent);


 Serial.println("UNO Slave with Wave Shield.");


  // Attempt to initialize SD card
 if (!card.init()) {
   Serial.println("SD card init failed!");
   /* SD card is not in correct, or not recognized by Arduino */
   return;
 }
 if (!vol.init(card)) {  // Attempt to initialize volume
   Serial.println("Volume init failed!");
   return;
   /* Adjust volume settings in WaveHC.h; DVOLUME must be set to non-zero if not using digital volume controls*/


 }
 if (!root.openRoot(vol)) { Attempt to open root directory
   Serial.println("Opening root failed!"); /* SD card cannot be accessed, restricted    
   by encrypted SD or other reason? idk dude */
   return;
 }


 Serial.println("all set"); // Everything initialized correctly
}


void loop() {
 // Nothing to do here
}


void receiveEvent(int howMany) {
 // Checking if the correct number of bytes sent by master
 if (howMany != 4) {
   Serial.println("Incorrect byte count received.");
   return;
 }


 unsigned long receivedTagID = 0;
 while (Wire.available()) {
   receivedTagID = (receivedTagID << 8) | Wire.read(); // Receiving bytes from master
 }


 Serial.print("Received Tag ID: "); 
 Serial.println(receivedTagID); // Print ID tag to confirm it’s correct


 for (int k = 0; k < 3; k++) { // Iterate through Pill object array, can adjust to match pill array size
   if (pills[k].ID == receivedTagID) { // Play associated file if received tag matches tag of a Pill object
     Serial.println("match"); // Announce a match has been found
     Serial.println(pills[k].filename); // Print filename found
     playFile(pills[k].filename); // Run playFile function
   }
 }
}


void playFile(String filename) {
 char charArray[6];  // Stores char array version of filename
 filename.toCharArray(charArray, sizeof(charArray)); // Converts filename to char array
 Serial.println(charArray); // Print the charArray to double check manually
  // Open the file from the root
 if (!file.open(root, charArray)) {
   Serial.print("Couldn't open file: "); // Something wrong with the array
   Serial.println(charArray);
   return;
 }
  // Prepare the wave object
 if (!wave.create(file)) {
   Serial.println("Couldn't create wave"); // Wave object not made,
   return;
 }


 wave.play();  // Play the sound
}
