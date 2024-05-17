#ifdef ESP8266
#include <ESP8266WiFi.h>
#endif
#include <Arduino.h>
#include <esp_task_wdt.h>
#include <Arduboy2.h>
#include <FS.h>
#include <SD.h>
//#include <ArduboyTones.h>
#include "Game.h"
#include "Draw.h"
#include "FixedMath.h"
#include "Platform.h"
#include "Keyboard.h"
#include <Update.h>
#include <cstring>

#define ESP32
Arduboy2Base arduboy;
Keyboard kb;
// ArduboyTones sound(arduboy.audio.enabled);
Sprites sprites;


#define EEPROM_NEEDED_BYTES 1024

void performUpdate(Stream &updateSource, size_t updateSize) {
    Serial.println("start uploading");
    if (Update.begin(updateSize)) {      
        Serial.println("done uploading");
        size_t written = Update.writeStream(updateSource);
        
        if (written == updateSize) {
            Serial.println("Written : " + String(written) + " successfully");
        }
        else {
            Serial.println("Written only : " + String(written) + "/" + String(updateSize) + ". Retry?");
        }
        if (Update.end()) {
            Serial.println("OTA done!");
            if (Update.isFinished()) {
                Serial.println("Update successfully completed. Rebooting.");
            }
            else {
                Serial.println("Update not finished? Something went wrong!");
            }
        }
        else {
            Serial.println("Error Occurred. Error #: " + String(Update.getError()));
        }

    }
    else {
        Serial.println("Not enough space to begin OTA");
    }
}

// check given FS for valid update.bin and perform update if available
void updateFromFS(fs::FS &fs, std::string path) {
    esp_task_wdt_init(30, false);
    Serial.println("loading...");
    File updateBin = fs.open(path.c_str());
    if (updateBin) {
        if(updateBin.isDirectory()){
            Serial.println(("Error, " + path + " is not a file").c_str());
            updateBin.close();
            return;
        }

        size_t updateSize = updateBin.size();

        if (updateSize > 0) {
            Serial.println("Try to start update");
            vTaskDelete(arduboy.displayHandle);
            performUpdate(updateBin, updateSize);
        }
        else {
            Serial.println("Error, file is empty");
        }

        updateBin.close();
    
        // whe finished remove the binary from sd card to indicate end of the process
        //fs.remove("/update.bin");      
    }
    else {
        Serial.println("Could not load update.bin from sd root");
    }
}

void rebootEspWithReason(std::string reason) {
    Serial.println(reason.c_str());
    delay(100);
    ESP.restart();
}

uint8_t Platform::GetInput()
{
  uint8_t result = 0;
  
  if(kb.getRisingEdgeKey() == std::make_pair(2, 4))
  {
    result |= INPUT_A;  
  }
  if(kb.getRisingEdgeKey() == std::make_pair(2, 5))
  {
    result |= INPUT_B;  
  }
  if(kb.getKey(1, 1).getIsPressed())
  {
    result |= INPUT_UP;  
  }
  if(kb.getKey(3, 1).getIsPressed())
  {
    result |= INPUT_DOWN;  
  }
  if(kb.getKey(2, 0).getIsPressed())
  {
    result |= INPUT_LEFT;  
  }
  if(kb.getKey(2, 2).getIsPressed())
  {
    result |= INPUT_RIGHT;  
  }

  return result;
}

void Platform::PlaySound(const uint16_t* audioPattern)
{
	// sound.tones(audioPattern);
}

void Platform::SetLED(uint8_t r, uint8_t g, uint8_t b)
{
  arduboy.setRGBled(r, g, b);
}

void Platform::PutPixel(uint8_t x, uint8_t y, uint8_t colour)
{
  arduboy.drawPixel(x, y, colour);
}

// Adpated from https://github.com/a1k0n/arduboy3d/blob/master/draw.cpp
// since the AVR has no barrel shifter, we'll do a progmem lookup
const uint8_t topmask_[] PROGMEM = {
  0xff, 0xfe, 0xfc, 0xf8, 0xf0, 0xe0, 0xc0, 0x80 };
const uint8_t bottommask_[] PROGMEM = {
  0x01, 0x03, 0x07, 0x0f, 0x1f, 0x3f, 0x7f, 0xff };

void Platform::DrawVLine(uint8_t x, int8_t y0_, int8_t y1_, uint8_t pattern) 
{
  uint8_t *screenptr = arduboy.getBuffer() + x;

  if (y1_ < y0_ || y1_ < 0 || y0_ > 63) return;

  // clip (FIXME; clipping should be handled elsewhere)
  // cast to unsigned after clipping to simplify generated code below
  uint8_t y0 = y0_, y1 = y1_;
  if (y0_ < 0) y0 = 0;
  if (y1_ > 63) y1 = 63;

  uint8_t *page0 = screenptr + ((y0 & 0x38) << 4);
  uint8_t *page1 = screenptr + ((y1 & 0x38) << 4);
  if (page0 == page1) 
  {
    uint8_t mask = pgm_read_byte(topmask_ + (y0 & 7))
      & pgm_read_byte(bottommask_ + (y1 & 7));
    *page0 &= ~mask;
    *page0 |= pattern & mask;  // fill y0..y1 in same page in one shot
  }
  else
  {
    uint8_t mask = pgm_read_byte(topmask_ + (y0 & 7));
    *page0 &= ~mask;
    *page0 |= pattern & mask;  // write top 1..8 pixels
    page0 += 128;
    while (page0 != page1) 
    {
      *page0 = pattern;  // fill middle 8 pixels at a time
      page0 += 128;
    }
    mask = pgm_read_byte(bottommask_ + (y1 & 7));  // and bottom 1..8 pixels
    *page0 &= ~mask;
    *page0 |= pattern & mask;
  }
}

uint8_t* Platform::GetScreenBuffer()
{
  return arduboy.getBuffer();
}

void Platform::DrawSprite(int16_t x, int16_t y, const uint8_t *bitmap, uint8_t frame)
{
  sprites.drawPlusMask(x, y, bitmap, frame);
}

void Platform::DrawSprite(int16_t x, int16_t y, const uint8_t *bitmap,
  const uint8_t *mask, uint8_t frame, uint8_t mask_frame)
{
  sprites.drawExternalMask(x, y, bitmap, mask, frame, mask_frame);
}

void Platform::DrawBitmap(int16_t x, int16_t y, const uint8_t *bitmap)
{
  uint8_t w = pgm_read_byte(&bitmap[0]);
  uint8_t h = pgm_read_byte(&bitmap[1]);
  arduboy.drawBitmap(x, y, bitmap + 2, w, h);
}

void Platform::DrawSolidBitmap(int16_t x, int16_t y, const uint8_t *bitmap)
{
  uint8_t w = pgm_read_byte(&bitmap[0]);
  uint8_t h = pgm_read_byte(&bitmap[1]);
  arduboy.fillRect(x, y, w, h, BLACK);
  arduboy.drawBitmap(x, y, bitmap + 2, w, h);
}

void Platform::FillScreen(uint8_t colour)
{
  arduboy.fillScreen(colour);
}

unsigned long lastTimingSample;

bool Platform::IsAudioEnabled()
{
	return arduboy.audio.enabled();
}

void Platform::SetAudioEnabled(bool isEnabled)
{
	if(isEnabled)
		arduboy.audio.on();
	else
		arduboy.audio.off();
}

void Platform::ExpectLoadDelay()
{
	// Resets the timer so that we don't tick multiple times after a level load
	lastTimingSample = millis();
}

void setup(){
  //WiFi.mode(WIFI_OFF);
  Serial.begin(115200);
  uint8_t cardType;
    u8g2.begin();
  
  // i think this is only needed for the esp8266 eeprom emulation
  //EEPROM.begin(EEPROM_NEEDED_BYTES);
   if (!SD.begin(4)) {
      rebootEspWithReason("Card Mount Failed");
   }

   cardType = SD.cardType();

   if (cardType == CARD_NONE) {
      rebootEspWithReason("No SD_MMC card attached");
   }
   kb.init();
  arduboy.begin();
  //arduboy.boot();
  //arduboy.clear();
  //arduboy.initDraw();
  //delay(1000);
  //Serial.println("rerfrffaaref");
  //vTaskDelete(arduboy.displayHandle);
  //arduboy.stop();
  //    Serial.println("uploading new software");
  //      //arduboy.flashlight();
  //      updateFromFS(SD, "/main.bin");
  //      rebootEspWithReason("main uploaded!!");
  //arduboy.initDraw();
//  arduboy.boot(); 
//  arduboy.flashlight();
//  arduboy.systemButtons();
//  arduboy.bootLogo();
//  arduboy.audio.off();
  // Serial.begin(9600);
//  SeedRandom((uint16_t) arduboy.generateRandomSeed());


   // You can uncomment this and build again
   // Serial.println("Update successfull");

   //first init and check SD card

  arduboy.setFrameRate(TARGET_FRAMERATE);
  Game::Init();
  lastTimingSample = millis();
}


void loop(){
  //Serial.println("loop!");
  
  static int16_t tickAccum = 0;
  unsigned long timingSample = millis();
  tickAccum += (timingSample - lastTimingSample);
  lastTimingSample = timingSample;
	
#if DEV_MODE
  if(arduboy.nextFrameDEV())
#else
  if(arduboy.nextFrame())
#endif
  {
	constexpr int16_t frameDuration = 1000 / TARGET_FRAMERATE;
  bool flag = false;
	while(tickAccum > frameDuration)
	{
		Game::Tick();
		tickAccum -= frameDuration;
    kb.update();
    if (kb.getRisingEdgeKey() == std::make_pair(0, 0)) {
        flag = true;
        break;
    }
    //Serial.println("fgohoj");
	}
  if (flag) {
      
    Serial.println("uploading new software");
        //arduboy.flashlight();
        updateFromFS(SD, "/main.bin");
        rebootEspWithReason("main uploaded!!");
  }
	
	Game::Draw();
    
  //Serial.write(arduboy.getBuffer(), 128 * 64 / 8);

#if DEV_MODE
	// CPU load bar graph	
	int load = arduboy.cpuLoad();
	uint8_t* screenPtr = arduboy.getBuffer();
	
	for(int x = 0; x < load && x < 128; x++)
	{
		screenPtr[x] = (screenPtr[x] & 0xf8) | 3;
	}
	screenPtr[100] = 0;
#endif
	
    arduboy.display(false);
  }
}
