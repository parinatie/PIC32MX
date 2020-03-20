# PIC32MX
## PIC 32MX DEVELOPMENT BOARD USER’S GUIDE

![](https://github.com/parinatie/PIC32MX/blob/master/images/PIC32MX1.png)

## Introduction
Thank you for purchasing the Swadeshee Parinati PIC32MX Development Board. This board provides a low-cost, modular development system for Microchip’s PIC32MX 32-bit microcontroller. The Development Board comes pre-loaded with demonstration software for the user to explore the new features of the PIC32MX. It is also expandable through pin headers for external interface, which allows the user to extend its functionality. The PIC32MX Development Board also supplies on-board circuitry and consists of bootloader firmware for flash programming with USB port.

## PIC32MX Development Board Functionality & Features
A representation of the layout of the PIC32MX Development Board is shown in Figure 1-1. The board includes these key features, as indicated in the diagram:

    1. PIC32MX795F512L 32-bit microcontroller
    2. USB Bootloader for Flash programming
    3. Red power-indicator LED
    4. Regulated +5V and +3.3V power supply for powering the board via USB or external DC source.
    5. On-board crystal for precision microcontroller clocking (8 MHz)
    6. On-board 32kHz crystal for RTC applications
    7. USB connectivity
    8. 2X16 LCD display
    9. Four push-button switches for user-defined inputs and additional push button for microcontroller reset
    10. Four user-defined indicator LEDs
    11. 6-pin ICSP header for flash programmer interface
    12. Dedicated pin headers for BLE and ESP8266 modules (Modules not included)
    13. On-board Potentiometer for ADC input and LM35 temperature sensor
    14. On-board MCP3201 12-bit A/D converter with SPI interface
    15. On-board EEPROM with I2C interface
    16. Jumpers for shared I/O pins with on-board peripherals 
    17. On-board 12V SPDT relay for power load switching

## Host Computer Requirements
To communicate with and program the development board, the following hardware and software requirements must be met:
* PC-compatible system
* An available USB port on PC or powered USB hub
* Windows OS

## Software Installation
### MPLABX IDE: 
1. Download the latest version of MPLABX IDE from: https://www.microchip.com/mplab/mplab-x-ide
2. Install the IDE in your computer
### XC32 C Compiler:
1. Download the latest version of the XC32 C compiler from: https://www.microchip.com/mplab/compilers
2. Install XC32 compiler in your system.

## Creating a Project
1. Launch the MPLAB X IDE
2. Under file menu click on New Project or use hotkey Ctrl+Shift+N 
