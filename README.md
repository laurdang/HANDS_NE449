# Introduction

We developed the Haptic Assisted Navigation Detection and Scanner (H.A.N.D.S.),  a device capable of assisting visually impaired individuals in navigating enclosed spaces (e.g. an office or kitchen). This device, worn on the hand, provides a multisensory approach to navigation that is both intuitive and adaptable to user needs. We integrated Arduino hardware (programmed with Arduino IDE v.2.3.4), distance sensors, haptic feedback motors, and a Radio Frequency Identification (RFID) module to develop the initial prototype of H.A.N.D.S. H.A.N.D.S. implements vibrotactile feedback to assist with spatial navigation and orientation through the distance sensors and haptic feedback motors, and helps users identify objects through the RFID scanner and audio player. The RFID implementation not only identifies objects, but it can also provide information about an object’s characteristics (e.g. dosage of a medication or the color of a shirt). This initial prototype can be used to inform future iterations of a device that can assist visually impaired individuals with both spatial navigation and object recognition, providing them with a greater sense of autonomy in daily tasks and enhance spatial awareness in a broad range of selected environments.

https://github.com/user-attachments/assets/359187c9-9fce-4a8a-9d6c-ddbca6e98cfe

# Set-up
## Hardware:
- Arduino Uno Rev3
- Arduino Mega 2560 Rev3
- Adafruit Wave Shield™  v1.1
- HitLetgo RFID Kit – Mifare RC522 RF IC Card Sensor Module (compact radio-frequency identification system used for short-range wireless communication)
- 2 Adafruit™ VL53L0X  distance ranging sensors (small, laser-based ranging module that measures the distance to an object by calculating the time it takes for an emitted infrared light pulse to reflect back to the sensor)
- 2 Adafruit Vibrating Mini Motor Discs (haptic feedback motor)
- Breadboard
- Babiqt Mifare RFID Stickers 1K Mifare chip and 13.56MHz working frequency (pre-labelled stickers for RFID detection)
- 128GB SD Card
- Velcro finger splint

### Prototype and Schematic:

 ![Hands Prototype Hardware](/Media/HANDS_Prototype_Hardware.png)
 ![Hands Prototype Schematic](/Media/HANDS_Prototype_Schematic.png)
 > Motor disc pins changed to 13 and 2


## Software:
| Board | File(s) |
| ------------- | ------------- |
| Arduino Mega 2560 Rev3  | ```HANDS_FINAL_MASTER.ino```  |
| Arduino Uno Rev3/Adafruit Wave Shield™  v1.1 | ```HANDS_FINAL_SLAVE.ino``` + ```Pill.h``` + ```Pill.cpp```|

Download ```HANDS_FINAL_MASTER.ino``` and ```HANDS_FINAL_SLAVE.ino``` and place them in separate folders. Add ```Pill.h``` and ```Pill.cpp``` to the Slave folder. Plug both Arduinos to the same adaptor connected to the same computer, upload the Slave and Master file to the appropriate board/port. You should be able to see both boards communicating with the Serial Monitor in their respective windows.

### Notes:
- Use code in I2C implementation and Component testing folder to check communication between modules and boards

## Libraries
- [Adafruit_VL53L0X library](https://learn.adafruit.com/bluefruit-nrf52-feather-learning-guide/arduino-bsp-setup)
- [MFRC522 library](https://github.com/miguelbalboa/rfid)
- [Adafruit_WaveHC library](https://github.com/adafruit/WaveHC)
- Arduino Wire library

