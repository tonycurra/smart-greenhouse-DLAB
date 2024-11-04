# Smart-Greenhouse-DLAB

**Smart-Greenhouse-DLAB** is an open-source, high-tech greenhouse solution for university startups and research labs. Designed as a pre-incubation tool, this greenhouse offers automated lighting, ventilation, and environmental monitoring. It enables students, researchers, and professionals to experiment with controlled agriculture setups to advance sustainable agritech innovations.

## Table of Contents
- [Features](#features)
- [Getting Started](#getting-started)
- [Installation](#installation)
- [Usage](#usage)
- [Contributing](#contributing)
- [License](#license)

## Features

- **Automated Lighting**: Schedule LED lighting cycles to optimize plant growth.
- **Ventilation Control**: Automatic fan activation to manage LED temperature.
- **Environmental Monitoring**: Options to add sensors for temperature, humidity, and light levels.
- **Modular Design**: Easily upgrade or add new features, such as irrigation or CO₂ control.
- **Education-Focused**: Ideal for students, researchers, and innovators in agritech.

## Getting Started

### Prerequisites
- **Hardware**: ESP32-C3 microcontroller, relay modules, LED grow lights, ventilation fan, and optional sensors (e.g., DHT22 for temperature and humidity).
- **Software**: [Arduino IDE](https://www.arduino.cc/en/software), Wi-Fi connectivity for NTP time synchronization.

### Setup Overview
1. **Mechanical Setup**: Assemble the greenhouse frame, LED lights, and fan.
2. **Wiring**: Connect the ESP32-C3, relay modules, LED lights, and ventilation fan.
3. **Code Upload**: Use Arduino IDE to upload the control code (provided below) to the ESP32-C3.

## Installation

1. Clone this repository:
   ```bash
   git clone https://github.com/yourusername/Smart-Greenhouse-DLAB.git
   cd Smart-Greenhouse-DLAB
