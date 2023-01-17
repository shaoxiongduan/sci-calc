#ifndef MACROPAD_H
#define MACROPAD_H

#include "Util.h"
#include "Keyboard.h"

extern Keyboard kb;

class Macro {
    public:
        Macro();

        Macro(std::vector <uint8_t> keys);

        void writeMacro();

        std::string getMacroString();

    private:
        std::vector <uint8_t> keys;
};

class Layout {
    public:
        Layout(std::string name, Macro macros[ROWCNT][COLCNT]);

        std::string getName();

        Macro getMacro(int row, int col);
        
    private:
        std::string name;
        Macro macros[ROWCNT][COLCNT];
};

class MacroPad {
    public:
        MacroPad(std::vector <Layout> layouts);

        void update();

        bool curIsHeld();

        void draw();

    private:
        std::vector <Layout> layouts;
        int curLayout;
        float prevtime;
        std::pair <byte, byte> curPressed;
};

#endif