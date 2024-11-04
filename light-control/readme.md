
# Light-Control Module for Smart-Greenhouse-DLAB

This **Light-Control Module** automates the lighting schedule in **Smart-Greenhouse-DLAB**. It manages LED grow lights using an ESP32 microcontroller and relay to optimize plant growth by simulating natural day-night cycles.

## Features
- **Automated Lighting Schedule**: Lights turn on at 8 AM and off at 9 PM (adjustable in code).
- **Relay-Controlled Switching**: Controls LED lights through a relay connected to the ESP32.
- **Modular Design**: Part of the larger Smart-Greenhouse-DLAB system, can be adapted or integrated with additional modules.

## Getting Started

### Hardware Requirements
- **ESP32-C3 Microcontroller**: Controls the lighting relay based on time.
- **Relay Module**: Switches LED lights on and off as per the schedule.
- **LED Grow Lights**: Provide the necessary light spectrum for plant growth.

### Wiring Instructions
1. Connect the **relay module** to the **ESP32-C3**:
   - **Relay IN pin** to **ESP32 digital pin 4** (adjustable in code).
   - **Relay VCC and GND** to ESP32 **3.3V** and **GND**.
2. Connect **LED grow lights** to the relay’s **normally open (NO)** terminal, with appropriate power connections.

### Software Setup
1. Open `LightControl.ino` in the Arduino IDE.
2. Replace `your_SSID` and `your_PASSWORD` with your Wi-Fi credentials for NTP time synchronization.
3. Upload the code to the ESP32.

## Code Overview

The code turns the lights on at 8 AM and off at 9 PM. These times are customizable by editing the `if` conditions in the main `loop()`.

### Example Code Snippet
```cpp
#include <WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

// Replace with your network credentials
const char *ssid = "DemonstratorLab";
const char *password = "10000ways";

// Define NTP client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", 0, 60000); // UTC timezone, sync every 60 seconds

// Define pin for relay
const int relayPin = 4;

void setup() {
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Initialize the relay pin as an output
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW);  // Start with relay off

  // Initialize NTP client
  timeClient.begin();
}

void loop() {
  timeClient.update();

  // Get current hour in 24-hour format
  int currentHour = timeClient.getHours();

  // Turn relay on at 8 AM and off at 9 PM
  if (currentHour >= 8 && currentHour < 21) {  // From 8 AM to before 9 PM
    digitalWrite(relayPin, HIGH);  // Relay ON
    Serial.println("Relay is ON");
  } else {
    digitalWrite(relayPin, LOW);   // Relay OFF
    Serial.println("Relay is OFF");
  }

  delay(10000);  // Update every 10 seconds
}
```

### Adjusting the Lighting Schedule
To change the lighting schedule:
- Modify the `if` condition in the `loop()` to adjust `currentHour` values.

For example:
```cpp
// Turn lights on at 7 AM and off at 8 PM
if (currentHour >= 7 && currentHour < 20) {
  digitalWrite(relayPin, HIGH);  // Relay ON
} else {
  digitalWrite(relayPin, LOW);   // Relay OFF
}
```

## Troubleshooting
- **Wi-Fi Connection Issues**: Verify your SSID and password.
- **Relay Not Switching**: Ensure the relay is connected to the correct GPIO pin and LED lights are properly wired.
- **Time Sync Issues**: The ESP32 needs Wi-Fi access to get the correct time from NTP servers.

## Future Enhancements
- Add a manual override switch for lights.
- Integrate light intensity control based on plant requirements.

## License
This module is part of the open-source Smart-Greenhouse-DLAB project and is licensed under the MIT License.
