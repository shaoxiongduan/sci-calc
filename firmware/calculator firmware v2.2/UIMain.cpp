#include "UIMain.h"

std::string clipboard = "";

Keyboard kb;
bool angleMode = 0; // 0: radians, 1: degree

ESP32Time rtc(8 * 3600);


Macro layout1[5][6] = {
    {Macro({KEY_ESC}),          Macro({'/'}), Macro({'*'}), Macro({'-'}),           Macro({KEY_LEFT_GUI, 'a'}, "CMD+A"), Macro({KEY_LEFT_GUI, 'r'}, "CMD+R")},
    {Macro({'7'}),              Macro({'8'}), Macro({'9'}), Macro({'+'}),           Macro({KEY_LEFT_GUI, 'c'}, "COPY"),  Macro({KEY_LEFT_GUI, 'v'}, "PASTE")},
    {Macro({'4'}),              Macro({'5'}), Macro({'6'}), Macro({'^'}),           Macro({KEY_LEFT_GUI, 'x'}, "CUT"),   Macro({KEY_LEFT_GUI, 's'}, "SAVE")},
    {Macro({'1'}),              Macro({'2'}), Macro({'3'}), Macro({KEY_RETURN}),    Macro({KEY_LEFT_GUI, 'h'}, "HIDE"),  Macro({KEY_LEFT_GUI, 'n'}, "NEW")},
    {Macro({KEY_LAYER_SWITCH}), Macro({'0'}), Macro({'.'}), Macro({KEY_BACKSPACE}), Macro({KEY_AUTOCLICK}),                        Macro({'8'})}
};

Macro layout2[5][6] = {
    {Macro({KEY_ESC}),          Macro({'/'}),            Macro({'*'}),             Macro({'-'}),           Macro({KEY_LEFT_GUI, 'a'}, "CMD+A"), Macro({KEY_LEFT_GUI, 'r'}, "CMD+R")},
    {Macro({'7'}),              Macro({KEY_UP_ARROW}),   Macro({'9'}),             Macro({'+'}),           Macro({KEY_LEFT_GUI, 'c'}, "COPY"),  Macro({KEY_LEFT_GUI, 'v'}, "PASTE")},
    {Macro({KEY_LEFT_ARROW}),   Macro({'5'}),            Macro({KEY_RIGHT_ARROW}), Macro({'^'}),           Macro({KEY_LEFT_GUI, 'x'}, "CUT"),   Macro({KEY_LEFT_GUI, 's'}, "SAVE")},
    {Macro({'1'}),              Macro({KEY_DOWN_ARROW}), Macro({'3'}),             Macro({KEY_RETURN}),    Macro({KEY_LEFT_GUI, 'h'}, "HIDE"),  Macro({KEY_LEFT_GUI, 'n'}, "NEW")},
    {Macro({KEY_LAYER_SWITCH}), Macro({'0'}),            Macro({'.'}),             Macro({KEY_BACKSPACE}), Macro({'8'}),                        Macro({'8'})}
};

Macro layout4[5][6] = {
    {Macro({'q'}),          Macro({'w'}),            Macro({'e'}),             Macro({'r'}),           Macro({KEY_LEFT_GUI, 'a'}, "CMD+A"), Macro({KEY_LEFT_GUI, 'r'}, "CMD+R")},
    {Macro({'a'}),              Macro({'s'}),   Macro({'d'}),             Macro({'+'}),           Macro({KEY_LEFT_GUI, 'c'}, "COPY"),  Macro({KEY_LEFT_GUI, 'v'}, "PASTE")},
    {Macro({KEY_LEFT_ARROW}),   Macro({'5'}),            Macro({KEY_RIGHT_ARROW}), Macro({'^'}),           Macro({KEY_LEFT_GUI, 'x'}, "CUT"),   Macro({KEY_LEFT_GUI, 's'}, "SAVE")},
    {Macro({'1'}),              Macro({KEY_DOWN_ARROW}), Macro({'3'}),             Macro({KEY_RETURN}),    Macro({KEY_LEFT_GUI, 'h'}, "HIDE"),  Macro({KEY_LEFT_GUI, 'n'}, "NEW")},
    {Macro({KEY_LAYER_SWITCH}), Macro({'0'}),            Macro({'.'}),             Macro({KEY_BACKSPACE}), Macro({'8'}),                        Macro({'8'})}
};

MacroPad macroPad({ 
    Layout("standard", layout1),
    Layout("layout 2", layout2),
    Layout("minecraft", layout4)
});

MacropadUI macropadUI(&macroPad);



 
Macro layout3[5][6] = {
    {Macro({KEY_ESC}),          Macro({'/'}), Macro({'*'}), Macro({'-'}),           Macro({KEY_SIN}), Macro({KEY_SEC})},
    {Macro({'7'}),              Macro({'8'}), Macro({'9'}), Macro({'+'}),           Macro({KEY_COS}), Macro({KEY_CSC})},
    {Macro({'4'}),              Macro({'5'}), Macro({'6'}), Macro({'^'}),           Macro({KEY_TAN}), Macro({KEY_COT})},
    {Macro({'1'}),              Macro({'2'}), Macro({'3'}), Macro({KEY_RETURN}),    Macro({KEY_EXP}), Macro({'x'})},
    {Macro({KEY_LAYER_SWITCH}), Macro({'0'}), Macro({'.'}), Macro({KEY_BACKSPACE}), Macro({KEY_MODE_SWITCH}),     Macro({KEY_TAB})}
};

Macro layoutgame[5][6] = { 
    {Macro({KEY_ESC}),          Macro({'('}),            Macro({')'}),             Macro({'-'}),           Macro({KEY_ASIN}), Macro({KEY_SEC})},
    {Macro({'7'}),              Macro({KEY_UP_ARROW}),   Macro({'9'}),             Macro({'+'}),           Macro({KEY_ACOS}), Macro({KEY_CSC})},
    {Macro({KEY_LEFT_ARROW}),   Macro({'5'}),            Macro({KEY_RIGHT_ARROW}), Macro({KEY_SQRT}),      Macro({KEY_ATAN}), Macro({KEY_COT})},
    {Macro({'1'}),              Macro({KEY_DOWN_ARROW}), Macro({'3'}),             Macro({KEY_RETURN}),    Macro({KEY_LN}),   Macro({'y'})},
    {Macro({KEY_LAYER_SWITCH}), Macro({'0'}),            Macro({'.'}),             Macro({KEY_BACKSPACE}), Macro({KEY_MODE_SWITCH}),      Macro({KEY_TAB})}
};

InputBox inputBox(0, 0, 100, 12, 15);
Menu calcMenu(0, -70, 0, 0, 210, 48, 3);
InputBox expressionInput(0, 57, 210, 12, 42);
Checkbox checkbox1("test");
Slider slider1("Testval", 0, 100);


MacroPad calcLayout({
    Layout("1", layout3),
    Layout("2", layoutgame)
});

Menu menuSpecs(0, -70, 0, 0, 210, 64, 5, {
    new Text("Powered by an ESP32 WROOM-32E"), 
    new Text("Kailh choc switches"), 
    new Text("Designed by SHAO")
},
{
    nullptr,
    nullptr,
    nullptr
});

Menu menuSettings(0, -70, 0, 0, 210, 64, 5, {
    &checkbox1, 
    &slider1, 
    new Text("here.")
},
{
    &checkbox1,
    &slider1,
    nullptr
});

Menu menuMisc(0, -70, 0, 0, 210, 64, 4, {
    &inputBox,
    new Text("THOCC."), 
    new Text("CLACK.")
},
{
    &inputBox, 
    nullptr, 
    nullptr
});

Calculator calcMain(0, 0, 210, 64, &calcMenu, &expressionInput);


Menu programMenu(0, -70, 0, 0, 210, 64, 4, {
    new Text("Chess"),
    new Text("Spacetrash"),
    new Text("Snake"),
    new Text("Tetris"),
    new Text("Catacombs of the damned"),
    new Text("Squario"),
    new Text("Arduventure")
},
{
    new BinLink("/chess.bin"),
    new BinLink("/spacetrash.bin"),
    new BinLink("/snake.bin"),
    new BinLink("/tetris.bin"),
    new BinLink("/COTD.bin"),
    new BinLink("/squario.bin"),
    new BinLink("/arduventure.bin")
    
});

Menu stopwatchMenu(0, -70, 0, 0, 110, 64, 4);

StopwatchUI stopwatchUI(0, 0, 210, 64, &stopwatchMenu);

ChineseText ch1(1);
ChineseText ch2(2);
ChineseText ch3(3);

Menu mainMenu(-100, 0, 0, 0, 70, 64, 4, {
    new Text("Calculator"), 
    new Text("Macropad"), 
    new Text("Programs"), 
    new Text("Stopwatch"),
    new Text("Misc"),
    new Text("go learn"),
    new Text("ap"),
    new Text("satan"),
    new Text("Debug"), 
    new Text("Specs"), 
    new Text("Settings")
},
{
    &calcMain, 
    &macropadUI, 
    &programMenu, 
    &stopwatchUI,
    &menuMisc, 
    &ch1,
    &ch2,
    &ch3,
    nullptr, 
    &menuSpecs, 
    &menuSettings
});


UIElement* currentElement = &mainMenu;

void displayTime() {
    if (currentElement == &mainMenu) {
        u8g2.setFont(u8g2_font_inb19_mf);
        u8g2.drawStr(80, 35, rtc.getTime("%H:%M:%S").c_str());
        u8g2.setFont(u8g2_font_profont10_mf);
        u8g2.drawStr(80, 55, rtc.getTime("%A, %B %d %Y").c_str());
        u8g2.setFont(u8g2_font_profont10_mf);
    }
    //struct tm timeinfo = rtc.getTimeStruct();
}