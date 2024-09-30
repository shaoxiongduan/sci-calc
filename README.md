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

The source code for the sci-calc is structured as follows

Folders:
```
Animation
Calculator
Macropad
Stopwatch
UIElements
Utils
```
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
