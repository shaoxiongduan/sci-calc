# sci-calc

## Assembly Guide

[link](https://youtu.be/RY_riS_9hHA?si=YKYpsfk6U_JUeETe)

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

#### layout (might change):

![keyboard-layout](https://user-images.githubusercontent.com/46639847/219936715-6f4ded29-5113-45ce-979c-dd3f59f1f1b0.png)

when inputting expressions, switch layer is needed to move the cursor left or right, whereas in the history menu(and all of the other menus), holding switch layer is not necessary to use the arrow keys.
when in the history menu, use the arrow keys to navigate up/down, and press enter to copy the selected expression's answer to the input box.
#### video demo

https://user-images.githubusercontent.com/46639847/219936733-cb611f87-4cae-4c7e-8eed-b2f6bcc909a7.mp4

### Macropad

A bluetooth numpad that comes with 10 customizable macro keys, though all keys can be customized, only the 10 keys on the 2 rightmost rows can be displayed on the screen.
Macros and layers are very easy to create in code (see firmware), and I'm planning to make it possible to change and edit the layout via a text file in the SD card.


#### video demo

https://user-images.githubusercontent.com/46639847/219937053-a5f0e39d-01d1-4069-9902-0d509ead685e.mp4

### Programs

It is possible to upload your own code to the sci-calc by copying the .bin file that you compiled onto the SD card and creating a menu link to it in the main firmware code (see firmware), but this is kinda complicated and I'm trying to make it automatically create the link.
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

# Layouts

## Games

### Layout for Chess:

![chess-sci-calc](https://github.com/shaoxiongduan/sci-calc/assets/46639847/9d19d974-8d25-4da9-8d7f-b4a2141a5090)


### Layout for Spacetrash:
![spacetrash-sci-calc](https://github.com/shaoxiongduan/sci-calc/assets/46639847/50851d95-2496-45ed-9129-2f148198e5c8)


### Layout of COTD:
![cotd-sci-calc](https://github.com/shaoxiongduan/sci-calc/assets/46639847/7e149da6-6c71-402f-a621-6d513af9648c)

### Layout of Snake:

![snake-sci-calc](https://github.com/shaoxiongduan/sci-calc/assets/46639847/48013a89-706d-405d-9e11-df125deea777)


### Layout of Squario:

![squario-sci-calc](https://github.com/shaoxiongduan/sci-calc/assets/46639847/86526f6b-1b7d-434d-a216-5f713a8d3a90)


### Layout of Tetris:
![tetris-sci-calc](https://github.com/shaoxiongduan/sci-calc/assets/46639847/0ceca725-5f8c-4282-be3c-df19f8a441d0)


# Troubleshooting
## Not turning on

1. Check the power indicator lights: if it's off, then the battery is drained. Charge it.
2. Some models have a protective sticker at the bottom of the microSD card that makes the connection unstable. Removing it will make connections a lot better.

If the lights are on:
1. The microSD card is loose. Gently push the card in until the screen lights up. Or if you want to be sure, connect the SCI-CALC to your computer via a data usb-c cable and open the serial monitor (baud rate 115200). 
2. The OLED screen module is misaligned. Check the pogo pins on the left side. If misaligned, loosen the screws on the top plate holding the module down, and push the module to the left until the pogo pins are touching the pads

# Updating Software

## How It Works

The SCI-CALC can load external programs through a SD card.
Each time you load a program, the SCI-CALC writes the contents of the corresponding ```.bin``` file to the ESP32's ROM. For instance, when you load up Chess, it overwrites the existing ```main.bin``` in the ROM to ```chess.bin```. When you press esc to go back, The ```main.bin``` from the SD-card is written back into the ROM. This allows us to update programs without having to use an IDE to upload. The idea is to update the ```.bin``` file of the program in the SD-card, and then load it to the ESP32.

## Updating Software (New)
To update the software for your sci-calc, follow these steps:
1. Get the .bin file you want to update from the ```/bin``` folder.
2. Copy that file over to the microSD card, replacing the old .bin file you want to update.
3. Navigate to the settings menu and activate Update from SD.
4. After it is done writing to ROM it should be properly updated!

## Updating Software (Old)
If you do not see the Update From SD option in the settings menu, follow these steps:
1. Get the .bin file you want to update from the ```/bin``` folder from this repo.
2. Copy that file over to the microSD card, replacing the old .bin file you want to update.
3. Navigate to the programs menu and enter any one of them.
4. once the game is loaded press esc to load the updated main.bin file back to the ESP32.
5. After it is done writing to ROM it should be properly updated!

For updating the main software, do these steps with the ```main.bin``` file. Or you can just replace everything in the SD-card with the contents in the ```/bin``` folder.

# Setting up the Dev Environment

## Arduino IDE
1. Install the Arduino IDE: https://www.arduino.cc/en/software
2. Install the drivers for the CH340 chip: https://learn.sparkfun.com/tutorials/how-to-install-ch340-drivers/all
3. Set up the Arduino IDE by following the steps for a regular ESP32 dev board: https://randomnerdtutorials.com/installing-esp32-arduino-ide-2-0/ (You don't have to do the test installation steps and the steps after)

4. Now you can start programming the SCI-CALC! When uploading, use the ESP32 Dev Board option for the board type.

# VSCode + PlatformIO

1. Install VSCode: https://code.visualstudio.com/
2. After installing VSCode, navigate to the extension tab on the left and install the PlatformIO extension: 
3. Clone this Github repo and open the ```sci_calc_code``` folder in VSCode with PlatformIO.
4. Navigate to the ```src``` folder to view and modify the source code. When done modifying, upload the code using the Upload button at the bottom.

# Code Structure

The source code for the sci-calc is structured as follows

Folders:

Animation
Calculator
Macropad
Stopwatch
UIElements
Utils

Files:
```
main.cpp/main.h
Sidebar.cpp/Sidebar.h
UIMain.cpp/UIMain.h
```

Now we will go into each part:
## Animation

The animation engine for the SCI-CALC works like this:

When you insert an animation, for instance this one:
```c++
insertAnimation(new Animation(subElements[i], BOUNCE, subElements[i] -> getX(), cnt * 12 + 12, 100));
```

The animation engine inserts the animation into the two pools depending on what you are animating (one for animating UIElements, one for animating variables)

```cpp
// An element might have multiple animations added to it at once, this mapping procedure makes sure that only the latest animation gets animated

void insertAnimation(Animation* animation) {
	if (animation -> getTargetElement() != nullptr) {
		animationsUI[animation -> getTargetElement()] = animation;
	}
	else {
		 nimationsInt[animation -> getTargetVal()] = animation;
	}
}
```

The animation scheduler then manages and updates the animations based on their duration and positions. This is done by calling their respective animation update functions based on their animation types.

See the code for more stuff.

## Calculator

The calculator folder contains all the regular and RPN calculator codes.

```Calculator.cpp/Calculator.h```: The UI Element for the scientific calculator. It wraps up the logic stuff to display the UI.

```Expression.cpp/Expression.h```
```Node.cpp/Node.h```
: This is where the calculations happen. The Expression class handles the tokenizing, tree-building, and evaluating of the expressions. The calculation module first takes in the input string from the Calculator UI's input box, and then parses it into mathematical tokens. It then uses the shunting-yard algorithm to build an abstract syntax tree (AST), which is used to do the actual calculations.


```ExpressionBlock.cpp/ExpressionBlock.h```
This is the UIElement for displaying the expressions in the history menu.

```CalculatorRPN.cpp/CalculatorRPN.h```
```EvaluatorRPN.cpp/EvaluatorRPN.h```
These classes are the UIElement components and the calculation part for the RPN calculator.

The RPN calculator has 5 registers: x, y, z, t, and a store register which is hidden. It supports basic stack manipulation operations like swap (x, y), push, and pop. I mainly referenced the HP RPN calculators and http://www.alcula.com/calculators/rpn/ when coding this.
