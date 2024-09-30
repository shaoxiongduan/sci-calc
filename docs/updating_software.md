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
