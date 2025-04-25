// //slave, receives alert to print/LED

// #include <Wire.h>

// #define LED_PIN 13  // Optional indicator LED
// #define SD_CS 10  // Confirm this is the CS pin for your Wave Shield

// void setup() {
//   pinMode(SD_CS, OUTPUT);
//   digitalWrite(SD_CS, HIGH);  // Disable SD card when not in use
//   Wire.begin(12);               // Must match Mega's address
//   Wire.onReceive(receiveEvent); // Attach receive event
//   Serial.begin(9600);

//   pinMode(LED_PIN, OUTPUT);
//   digitalWrite(LED_PIN, LOW);
// }

// void loop() {
//   // Idle; waiting for receiveEvent to be called
// }

// void receiveEvent(int howMany) {
//   char message[20];
//   int index = 0;

//   while (Wire.available() && index < sizeof(message) - 1) {
//     message[index++] = Wire.read();
//   }
//   message[index] = '\0';  // Null-terminate the string

//   Serial.print("Received: ");
//   Serial.println(message);

//   if (strcmp(message, "ALERT") == 0) {
//     Serial.println("Received");           // Respond to ALERT
//     digitalWrite(LED_PIN, HIGH);          // Optional: flash LED
//     delay(200);
//     digitalWrite(LED_PIN, LOW);
//   }
// }


// ==NEW==

#include <Wire.h>

#define SLAVE_ADDRESS 12      // Make sure this matches your Mega code
#define SD_CS 10              // Wave Shield's CS pin
#define LED_PIN 13            // Optional: LED to confirm communication

void setup() {
  Serial.begin(9600);

  // Disable Wave Shield (keep SD card inactive)
  pinMode(SD_CS, OUTPUT);
  digitalWrite(SD_CS, HIGH);   // Deselect SD card, prevent SPI from interfering

  Wire.begin(SLAVE_ADDRESS);   // Initialize I2C as slave at address 12
  Wire.onReceive(receiveEvent); // Attach receive event handler

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);   // Start with LED off

  Serial.println("UNO Slave ready with Wave Shield attached.");
}

void loop() {
  // Nothing needed here; waiting for I2C receive interrupts
}

void receiveEvent(int howMany) {
  char message[10];                    // Buffer for incoming message
  int index = 0;

  while (Wire.available() && index < sizeof(message) - 1) {
    message[index++] = Wire.read();
  }
  message[index] = '\0';               // Null-terminate the received string

  Serial.print("Received message: ");
  Serial.println(message);

  // Simple confirmation action
  if (strcmp(message, "ALERT") == 0) {
    Serial.println("Received");        // Confirmation message
    digitalWrite(LED_PIN, HIGH);       // Optional: flash LED to indicate success
    delay(200);
    digitalWrite(LED_PIN, LOW);
  }
}
