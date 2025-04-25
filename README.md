## 4/24 Update
To do:
1. Wire the Wave Shield and edit ```I2C_Check_SLAVE_RFID.ino``` to access and play files (use ```pill[index].filename```)
2. Check if distance mapping is correct in the Master code

Steps:
1. Use ```I2C_Check_SLAVE_RFID.ino``` and ```I2C_Check_MASTER_RFID.ino``` as the main working files (in I2C Implementation folder)
2. Redownload ```Pill.h``` and ```Pill.cpp``` and put them in the same folder as ```I2C_Check_SLAVE_RFID.ino```
3. Plug both Arduinos to the same adaptor connected to the same computer, upload the slave and master file to the appropriate board/port. You should be able to see both boards communicating with the Serial Monitor in their respective windows.

Notes:
- ```Pill.h```/```Pill.cpp``` only has a few of the RFIDs and will need to be updated later to play all of them
- Use ```I2C_Check_SLAVE.ino``` and ```I2C_Check_MASTER.ino``` to check communication between both boards (the RFID versions were based on this code)

## General
To download:

- [Adafruit_VL53L0X library](https://learn.adafruit.com/bluefruit-nrf52-feather-learning-guide/arduino-bsp-setup)
- [MFRC522 library](https://github.com/miguelbalboa/rfid)
- Wave library
- Pill.cpp
- Pill.h
