# sci-calc

## Overview

The sci-calc(I know, really creative name) is a 4-in-1 device, packing a scientific calculator, a macropad/numpad, a handheld game console, and a development board all into one neat and sleek little device.

## Specs
- Powered by an ESP32 WROOM32 E [datasheet](www.espressif.com/sites/default/files/documentation/esp32-wroom-32e_esp32-wroom-32ue_datasheet_en.pdf)
- Switches: kailh v1 choc switches
- Screen: 256x64 monochrome oled (display driver: SSD1322)
- Usb to serial chip: CH340C [driver download](learn.sparkfun.com/tutorials/how-to-install-ch340-drivers/all)
- Battery: any lipo battery under 1000mah would be fine
- SD card support(must be in FAT32 format)

## Function Keys
- Switch layer key: switches between different layout configurations
  - hold to switch to next layer, release to go back (like shift)
  - double press to switch to next layer and lock (like caps lock)
- deg/rad: used in the calculator program to switch between degree mode and radian mode
- tab: also used in the calculator program, it's used to switch between the input box and the list of previous calculations
## UI
### Calculator
A calculator with a history clipboard that can do basic arithmetic (add, subtract, multiply, divide, powers), as well as trigonmetric functions, natural logrithms and exponents. Equation solver and derivative calculator will come soon.

#### layout(might change):

![keyboard-layout](https://user-images.githubusercontent.com/46639847/219936715-6f4ded29-5113-45ce-979c-dd3f59f1f1b0.png)

when inputting expressions, switch layer is needed to move the cursor left or right, whereas in the history menu(and all of the other menus), holding switch layer is not necessary to use the arrow keys.
when in the history menu, use the arrow keys to navigate up/down, and press enter to copy the selected expression's answer to the input box.
#### video demo

https://user-images.githubusercontent.com/46639847/219936733-cb611f87-4cae-4c7e-8eed-b2f6bcc909a7.mp4

### Macropad

A bluetooth numpad that comes with 10 customizable macro keys, though all keys can be customized, only the 10 keys on the 2 rightmost rows can be displayed on the screen.
Macros and layers are very easy to create in code(see firmware), and I'm planning to make it possible to change and edit the layout via a text file in the SD card.


#### video demo

https://user-images.githubusercontent.com/46639847/219937053-a5f0e39d-01d1-4069-9902-0d509ead685e.mp4

### Programs

It is possible to upload your own code to the sci-calc by copying the .bin file that you compiled onto the SD card and creating a menu link to it in the main firmware code(see firmware), but this is kinda complicated and I'm trying to make it automatically create the link.
It's pretty easy to port code over to the sci-calc, just copy the Util.h, Util.cpp, Keyboard.h, Keyboard.cpp files over to your project and change the input checking functions.
Currently I've ported littlerookchess, spacetrash, snake, and tetris to it.

#### LittleRookChess
![image](https://user-images.githubusercontent.com/46639847/219938353-2eaa71d0-da5c-48c8-a9fe-db2489fa1074.png)

https://github.com/olikraus/u8g2/blob/master/sys/arduino/u8g2_page_buffer/LittleRookChess/LittleRookChess.ino
#### Spacetrash
![image](https://user-images.githubusercontent.com/46639847/219938377-4b7b2d2a-34c5-4b80-8309-64dda9d56ff3.png)

https://github.com/olikraus/u8g2/blob/master/sys/arduino/u8g2_page_buffer/SpaceTrash/SpaceTrash.ino
#### Snake
![image](https://user-images.githubusercontent.com/46639847/219938397-9109618b-9a15-4677-80f2-4d8203b3e311.png)

https://github.com/norbertg1/Snake-game
#### Tetris
![image](https://user-images.githubusercontent.com/46639847/219938416-7db0a753-4cb1-4768-a68c-06e84444e2fa.png)

https://github.com/Zimoslaw/TetriZimoslaw
