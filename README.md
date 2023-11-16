# WIO_Terminal_Game
# Arkanoido - WIO Terminal Edition

Welcome to Arkanoido, a simple Arkanoid-inspired game implemented on the WIO Terminal platform. This README provides essential information about the project, including hardware specifications, features, setup instructions, controls, gameplay, and more.

## Hardware Used

- **WIO Terminal**
  - Highly Integrated Design
    - MCU, LCD, WIFI, BT, IMU, Microphone, Speaker, microSD Card, Light Sensor, 5-Way Switch, Infrared Emitter (IR 940nm), Crypto-authentication Ready
  - Powered by Microchip ATSAMD51P19
    - ARM Cortex-M4F core running at 120MHz (Boost up to 200MHz)
    - 4 MB External Flash, 192 KB RAM
  - Comprehensive Protocol Support
    - SPI, I2C, I2S, ADC, DAC, PWM, UART(Serial)
  - Powerful Wireless Connectivity (supported only by Arduino)
    - Powered by Realtek RTL8720DN
    - Dual Band 2.4Ghz / 5Ghz Wi-Fi (802.11 a/b/g/n)
    - BLE / BLE 5.0

## Project Description

Arkanoido is a straightforward Arkanoid-inspired game designed for the WIO Terminal. The game features a spaceship (hero) that can be moved using the WIO Terminal's 5-way switch. The objective is to bounce a ball off the spaceship to destroy blocks and earn points.

## Gameplay

- **Objective:**
  - Bounce the ball off the spaceship to destroy blocks.
  - Earn points for each block destroyed.
  - Avoid letting the ball pass the spaceship to maintain lives.

- **Controls:**
  - **5-Way Switch:**
    - UP: Move the spaceship up
    - DOWN: Move the spaceship down
    - LEFT: Move the spaceship left
    - RIGHT: Move the spaceship right
    - PRESS: Not used in the current version

## Libraries Used

The project utilizes the following libraries:

1. **Free_Fonts**
   - Library for using different fonts in the project.
   - No additional setup is required; simply copy the library to the project.

2. **TFT_eSPI**
   - Library for interfacing with the TFT display.
   - Copy the library to the project to enable display functionality.

## Setup Instructions

1. **Install Arduino IDE**
   - Make sure you have the Arduino IDE installed on your development machine.

2. **Install Board Support for WIO Terminal**
   - Follow the instructions on the Seeed Studio website to install the board support for WIO Terminal in the Arduino IDE: [WIO Terminal Arduino Setup](https://wiki.seeedstudio.com/Wio-Terminal-Arduino-Setup/).

3. **Copy Libraries to the Project**
   - Copy the `Free_Fonts` and `TFT_eSPI` libraries to the `libraries` folder in your Arduino project directory.

4. **Open and Upload the Project**
   - Open the `Arkanoido_WIO_Terminal.ino` file in the Arduino IDE.
   - Connect the WIO Terminal to your computer.
   - Select the appropriate board and port.
   - Click the upload button to flash the project onto the WIO Terminal.

## Enjoy the Game!

Once the project is uploaded to the WIO Terminal, enjoy playing Arkanoido! Have fun exploring the capabilities of the WIO Terminal and tweaking the game to suit your preferences.

Feel free to modify and enhance the game as you see fit. If you encounter any issues or have suggestions for improvement, please refer to the project's GitHub repository for support and collaboration.
