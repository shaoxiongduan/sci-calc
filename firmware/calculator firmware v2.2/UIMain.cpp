#include "UIMain.h"


Macro layout3[5][6] = {
    {Macro({KEY_ESC}), Macro({'/'}), Macro({'*'}), Macro({'-'}), Macro({KEY_LEFT_GUI, 'a'}), Macro({'8'})},
    {Macro({'7'}), Macro({'8'}), Macro({'9'}), Macro({'+'}), Macro({KEY_LEFT_GUI, 'c'}), Macro({KEY_LEFT_GUI, 'v'})},
    {Macro({'4'}), Macro({'5'}), Macro({'6'}), Macro({'^'}), Macro({KEY_LEFT_GUI, 'x'}), Macro({KEY_LEFT_GUI, 's'})},
    {Macro({'1'}), Macro({'2'}), Macro({'3'}), Macro({KEY_RETURN}), Macro({'8'}), Macro({'8'})},
    {Macro({KEY_LAYER_SWITCH}), Macro({'0'}), Macro({'.'}), Macro({KEY_BACKSPACE}), Macro({'8'}), Macro({'8'})}
};

Macro layout4[5][6] = { 
    {Macro({KEY_ESC}), Macro({'('}), Macro({')'}), Macro({'-'}), Macro({'8'}), Macro({'8'})},
    {Macro({'7'}), Macro({KEY_UP_ARROW}), Macro({'9'}), Macro({'+'}), Macro({KEY_LEFT_GUI, 'c'}), Macro({KEY_LEFT_GUI, 'v'})},
    {Macro({KEY_LEFT_ARROW}), Macro({'5'}), Macro({KEY_RIGHT_ARROW}), Macro({KEY_LEFT_GUI, 'x'}), Macro({KEY_LEFT_GUI, 's'})},
    {Macro({'1'}), Macro({KEY_DOWN_ARROW}), Macro({'3'}), Macro({KEY_RETURN}), Macro({'8'}), Macro({'8'})},
    {Macro({KEY_LAYER_SWITCH}), Macro({'0'}), Macro({'.'}), Macro({KEY_BACKSPACE}), Macro({'8'}), Macro({'8'})}
};

InputBox inputBox(0, 0, 100, 12, 15);

MacroPad calcLayout({
    Layout("standard", layout3),
    Layout("layout 2", layout4)
});

Menu menuSpecs(0, 0, 256, 64, 5, {
    new Text("Powered by an ESP32 WROOM-32E"), 
    new Text("Kailh choc switches"), 
    new Text("Designed by SHAO")
},
{
    nullptr,
    nullptr,
    nullptr
});

Menu menuSettings(0, 0, 256, 64, 5, {
    new Text("Nothing"), 
    new Text("To see"), 
    new Text("here.")
},
{
    nullptr,
    nullptr,
    nullptr
});

Menu menuMisc(0, 0, 256, 64, 5, {
    &inputBox,
    new Text("THOCC."), 
    new Text("CLACK.")
},
{
    &inputBox, 
    nullptr, 
    nullptr
});


Menu menu(0, 0, 70, 64, 4, {
    new Text("Calculator"), 
    new Text("Macropad"), 
    new Text("Games"), 
    new Text("Misc"), 
    new Text("Debug"), 
    new Text("Specs"), 
    new Text("Settings")
},
{
    nullptr, 
    nullptr, 
    nullptr, 
    &menuMisc, 
    nullptr, 
    &menuSpecs, 
    &menuSettings
});


UIElement* currentElement = &menu;

