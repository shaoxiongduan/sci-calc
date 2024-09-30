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
