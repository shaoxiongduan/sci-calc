# sci-calc
<a href="https://github.com/shaoxiongduan/sci-calc/">
<img height=400 alt="Repo Banner - Awesome Repo Template" src="https://github.com/user-attachments/assets/1d2f0c47-30ca-4eb9-b335-ce44204528ab"></img></a>


<p align="center">
  <b>SCI-CALC: A Multifunctional Scientific Calculator</b>


  <br>
    <img title="Star on GitHub" src="https://img.shields.io/github/stars/shaoxiongduan/sci-calc.svg?style=for-the-badge&label=Star&color=999999">
  <a href="https://github.com/shaoxiongduan/sci-calc/fork">
    <img title="Fork on GitHub" src="https://img.shields.io/github/forks/shaoxiongduan/sci-calc.svg?style=for-the-badge&label=Fork&color=999999">
  </a>
  
  <a href = "https://discord.gg/ZbaYb36wnn">
<img src = "https://img.shields.io/discord/1259252001003536645?style=for-the-badge&label=Discord&color=7289DA">
  </a>
</p> 




## Overview

The sci-calc (I know, really creative name) is a 4-in-1 device, packing a scientific calculator, a macropad/numpad, a handheld game console, and a development board all into one neat and sleek little device.

## Specs
- Powered by an ESP32 WROOM32 E [datasheet](www.espressif.com/sites/default/files/documentation/esp32-wroom-32e_esp32-wroom-32ue_datasheet_en.pdf)
- Switches: kailh v1 choc switches
- Screen: 256x64 monochrome oled (display driver: SSD1322)
- Usb to serial chip: CH340C [driver download](learn.sparkfun.com/tutorials/how-to-install-ch340-drivers/all)
- Battery: any lipo battery under 1000mah would be fine
- SD card support (must be in FAT32 format)

## Function Keys
- Switch layer key: switches between different layout configurations
  - hold to switch to next layer, release to go back (like shift)
  - double press to switch to next layer and lock (like caps lock)
- deg/rad: used in the calculator program to switch between degree mode and radian mode
- tab: also used in the calculator program, it's used to switch between the input box and the list of previous calculations
## UI
### Calculator
A calculator with a history clipboard that can do basic arithmetic (add, subtract, multiply, divide, powers), as well as trigonmetric functions, natural logrithms and exponents. Equation solver and derivative calculator will come soon.

when inputting expressions, switch layer is needed to move the cursor left or right, whereas in the history menu(and all of the other menus), holding switch layer is not necessary to use the arrow keys.
when in the history menu, use the arrow keys to navigate up/down, and press enter to copy the selected expression's answer to the input box.

[Video Demo (Outdated)](https://user-images.githubusercontent.com/46639847/219936733-cb611f87-4cae-4c7e-8eed-b2f6bcc909a7.mp4)

### Macropad

A bluetooth numpad that comes with 10 customizable macro keys, though all keys can be customized, only the 10 keys on the 2 rightmost rows can be displayed on the screen.
Macros and layers are very easy to create in code (see firmware), and I'm planning to make it possible to change and edit the layout via a text file in the SD card.

[Video Demo (Outdated)](https://user-images.githubusercontent.com/46639847/219937053-a5f0e39d-01d1-4069-9902-0d509ead685e.mp4)

### Programs

It is possible to upload your own code to the sci-calc by copying the .bin file that you compiled onto the SD card and creating a menu link to it in the main firmware code (see firmware), but this is kinda complicated and I'm trying to make it automatically create the link.
It's pretty easy to port code over to the sci-calc, just copy the Util.h, Util.cpp, Keyboard.h, Keyboard.cpp files over to your project and change the input checking functions.
Currently I've ported littlerookchess, spacetrash, snake, and tetris to it.

[Game Demo](docs/game_demo.md)

## Assembly Guide
[link](https://youtu.be/RY_riS_9hHA?si=YKYpsfk6U_JUeETe)


# Layouts

[Layouts](docs/layout.md)

# Troubleshooting
[Troubleshooting](docs/troubleshooting.md)

# Updating Software
[Updating Software](docs/updating_software.md)

# Setting up the Dev Environment
[Environment Setup](docs/environment_setup.md)

# Code Structure
[Code Structure and Walkthrough](docs/code_structure.md)
