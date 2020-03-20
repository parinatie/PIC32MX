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
3. Select Microchip Embedded under categories and Standalone Project. Clik Next. (Refer Fig. 5.1)
![] (https://github.com/parinatie/PIC32MX/blob/master/images/Fig51.png)
Fig. 5.1
4.In device, type PIC32MX795F512L and click Next. (Refer Fig. 5.2)
![] (https://github.com/parinatie/PIC32MX/blob/master/images/Fig52.png)
Fig. 5.2
5. Under hardware tools, select Simulator if the target board has Bootloader. If there is no bootloader, select ICD3/4 or PICKit3/4 as per your needs. Click Next. (Refer Fig. 5.3)
![] (https://github.com/parinatie/PIC32MX/blob/master/images/Fig53.png)
Fig. 5.3
6. Under Compiler toolchains, select the latest version of XC32 and click Next. (Refer Fig. 5.4)
![] (https://github.com/parinatie/PIC32MX/blob/master/images/Fig54.png)
Fig. 5.4
7. Enter Project name without spaces, select a project folder and tick on Set as Main Project and click Finish. (Refer Fig. 5.5)
![] (https://github.com/parinatie/PIC32MX/blob/master/images/Fig55.png)
Fig. 5.5
8. Under Projects, a number of directories are listed on the left side of the window. (Refer Fig. 5.6)
![] (https://github.com/parinatie/PIC32MX/blob/master/images/Fig56.png)
Fig. 5.6
9. Right click on Source files and select New-> C Main File. (Refer Fig. 5.6)
10. In new window which appears, give a file name and keep extension as c and hit finish. (Refer Fig. 5.7)
![] (https://github.com/parinatie/PIC32MX/blob/master/images/Fig57.png)
Fig. 5.7
11. Under Window-> Target Memory View, select Configuration Bits. (Refer Fig. 5.8)
![] (https://github.com/parinatie/PIC32MX/blob/master/images/Fig58.png)
Fig. 5.8
12. Select the configuration bits as per requirement. Recommended bit configuration is shown in Fig. 5.9. Click Generate Source code to output.
![] (https://github.com/parinatie/PIC32MX/blob/master/images/Fig59.png)
Fig. 5.9
13. Copy the generated code and paste it to the top of the main file.(Refer Fig. 5.10)
![] (https://github.com/parinatie/PIC32MX/blob/master/images/Fig510.png)
Fig. 5.10
14. Write the code to blink the LED. (LED blink code is given in the next Section)
15. Save the file and click on Build Project or press F11.(Refer Fig. 5.11)
![] (https://github.com/parinatie/PIC32MX/blob/master/images/Fig511.png)
Fig. 5.11
16. Check if Build is successful. (Refer Fig. 5.12)
![] (https://github.com/parinatie/PIC32MX/blob/master/images/Fig512.png)
Fig. 5.12
17. Dashboard gives details about the memory usage.(Refer Fig. 5.13)
![] (https://github.com/parinatie/PIC32MX/blob/master/images/Fig513.png)
Fig. 5.13
