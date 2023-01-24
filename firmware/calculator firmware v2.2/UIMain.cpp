#include "UIMain.h"


Menu menuSpecs(0, 0, 256, 64, 5, {new Text("Powered by an ESP32 WROOM-32E"), new Text("Kailh choc switches"), new Text("Designed by SHAO")}, {nullptr, nullptr, nullptr});
Menu menuSettings(0, 0, 256, 64, 5, {new Text("Nothing"), new Text("To see"), new Text("here.")}, {nullptr, nullptr, nullptr});
Menu menuMisc(0, 0, 256, 64, 5, {new Text("CLICK."), new Text("THOCC."), new Text("CLACK.")}, {nullptr, nullptr, nullptr});


Menu menu(0, 0, 70, 64, 4, {new Text("Calculator"), new Text("Macropad"), new Text("Games"), new Text("Misc"), new Text("Debug"), new Text("Specs"), new Text("Settings")}, {nullptr, nullptr, nullptr, &menuMisc, nullptr, &menuSpecs, &menuSettings});


UIElement* currentElement = &menu;

