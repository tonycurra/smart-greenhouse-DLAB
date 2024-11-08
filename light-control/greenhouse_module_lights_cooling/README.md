
# Relay and Motor Control with Time Synchronization

This project uses an ESP32 microcontroller to control a relay and motor based on a real-time clock (RTC) synchronized with an NTP server. The relay (ventilation) and motor activate at specific times each day, even if WiFi disconnects temporarily.

## Folder Structure

- **RelayMotorControl/**: Main folder containing the code.
  - **RelayMotorControl.ino**: Arduino-compatible code file to control relay and motor.

## Features

- **Time-based Relay and Motor Control**: Relay (ventilation) and motor are activated or deactivated based on preset times.
- **NTP Time Synchronization**: Synchronizes time from an NTP server and keeps track of time internally if WiFi disconnects.
- **Customizable On/Off Times**: Easily adjust the relay and motor activation times by modifying the code.

## Requirements

- **ESP32-C3 Board** (or similar ESP32 board)
- **Motor Driver** connected to GPIO1 and GPIO2
- **Relay Module** connected to GPIO4
- **WiFi Connection** (for initial time synchronization)

## Setup Instructions

1. **Clone or Download** this repository.
   ```bash
   git clone https://github.com/yourusername/your-repo.git
   ```

2. **Open the Project**:
   - Open the `RelayMotorControl.ino` file in Arduino IDE.

3. **Configure Network Credentials**:
   - In the `RelayMotorControl.ino` file, update the `ssid` and `password` variables with your WiFi credentials.

4. **Upload the Code**:
   - Select your ESP32 board in Arduino IDE and upload the code.

## Usage

1. **Power On** your ESP32 board.
2. **Relay and Motor Control**:
   - The relay and motor will turn on at the specified `relayOnHour` and off at `relayOffHour`.
   - The motor’s operation is synced with the relay based on the preset times.

3. **Monitor Output**:
   - Use the Serial Monitor (115200 baud rate) to view status updates, including:
     - **Current Time** (hour, minute, and second)
     - **WiFi Status** (connected or disconnected)
     - **NTP Time Sync Status** (indicating if time is being synced from the internet)
     - **Ventilation and Relay Status** (indicating if ON or OFF)

## Customization

- **Change Relay On/Off Times**:
  - In `RelayMotorControl.ino`, adjust the values of `relayOnHour` and `relayOffHour` for custom activation times.

- **Adjust Motor Speed**:
  - Change the `motorSpeed` variable to set a new PWM speed for the motor.

## Example Serial Output

Upon running, the Serial Monitor provides detailed output such as:

```
Connecting to WiFi..
Connected to SSID: DemonstratorLab
IP Address: 192.168.1.100
Time synchronized from NTP successfully.

Current Time: 6:0:15
WiFi Status: Connected
Time Source: NTP (DemonstratorLab)
Relay is ON - Ventilation is ON
Motor is ON

...
```

This allows you to verify:
- If the time is being synced from the internet.
- The current time, WiFi connection status, and relay/motor states.

## License

This project is licensed under the MIT License. See the [LICENSE](../LICENSE) file for details.
