# SCI-CALC

## Overview

The SCI_CALC(I know, really creative name) is a 4-in-1 device, packing a scientific calculator, a macropad/numpad, a handheld game console, and a development board all into one neat and sleek little device.

## Specs
- Powered by an ESP32 WROOM32 E[datasheet](www.espressif.com/sites/default/files/documentation/esp32-wroom-32e_esp32-wroom-32ue_datasheet_en.pdf)
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
layout(might change):

![keyboard-layout](https://user-images.githubusercontent.com/46639847/219935671-401a025a-50ca-41fe-8419-fa750ff2e82f.png)


when inputting expressions, switch layer is needed to move the cursor left or right, whereas in the history menu(and all of the other menus), holding switch layer is not necessary to use the arrow keys.
when in the history menu, use the arrow keys to navigate up/down, and press enter to copy the selected expression's answer to the input box.
#### video demo


### Macropad:
	
