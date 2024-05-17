//#include <SPI.h>
//#include <EEPROM.h>

#ifdef ESP8266
#include <ESP8266WiFi.h>
#endif

#include <Arduboy2.h>
#include "SquarioGame.h"
#include "DefinesImagesAndSounds.h"
#include "Keyboard.h"
#define SOUNDPIN D3

Keyboard kb;
Arduboy2 display;
//ArduboyTones sound(display.audio.enabled);

SquarioGame Game( &display );

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
    //esp_task_wdt_init(30, false);
    Serial.println("displaying...");
    //u8g2.clearBuffer();
    Serial.println("clear!");
    //u8g2.sendBuffer();
    Serial.println("sent!");
    //u8g2.drawStr(10, 32, "writing main to ROM...");
    Serial.println("sent2!");
    //u8g2.sendBuffer();
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
            vTaskDelete(display.displayHandle);
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

char text[16];
uint32_t currTime;
uint32_t prevTime = 0;
bool SoundOn = false;

void setup() {
  //WiFi.mode(WIFI_OFF);
  EEPROM.begin(200);
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
  display.begin();
}


uint8_t RandomSeedSeed = 1;

void TitleScreen() {
  //if(SoundOn) sound.tones(Chorus);
  Game.ActivateButtonCD();
  while (true) {
    delay(10);
    kb.update();
    if ( Game.ButtonOffCD() ) {
      uint8_t input = display.buttonsState();
      if ( kb.getKey(2, 4).getIsPressed() || kb.getKey(2, 5).getIsPressed() ) break;
      //if ( ( input & LEFT_BUTTON ) || ( input & RIGHT_BUTTON ) ) SoundOn = !SoundOn;
      if (kb.getKey(1, 1).getIsPressed()) {
        if ( RandomSeedSeed == 255 ) RandomSeedSeed = 1;
        else RandomSeedSeed++;
      }
      if (kb.getKey(3, 1).getIsPressed()) { 
        if ( RandomSeedSeed == 1 ) RandomSeedSeed = 255;
        else RandomSeedSeed--;
      }
      if (kb.getKey(1, 1).getIsPressed() || kb.getKey(3, 1).getIsPressed() || kb.getKey(2, 4).getIsPressed() || kb.getKey(2, 5).getIsPressed() || kb.getKey(2, 0).getIsPressed() || kb.getKey(2, 2).getIsPressed()) Game.ActivateButtonCD( );
      if (kb.getRisingEdgeKey() == std::make_pair(0, 0)) {
        Serial.println("uploading new software");
        //arduboy.flashlight();
        updateFromFS(SD, "/main.bin");
        rebootEspWithReason("main uploaded!!");
      }
    }
    display.clear();
    display.drawBitmap(14,0,TitleSquarioText,96,32,1);
    display.drawBitmap(66,29,TitleSquarioGuys,53,32,1);
    display.setCursor(0,48); display.print(F("Seed:  ")); display.print(RandomSeedSeed);
    display.setCursor(0,56); display.print(F("Sound: "));
    if ( SoundOn ) display.print(F("On"));
    else display.print(F("Off"));
    display.display();
  }
  randomSeed( RandomSeedSeed );
  for ( uint8_t a = 0; a < GameSeeds; a++ ) Game.Seeds[a] = random( 255 );
}

const uint8_t *SFX = 0;
const uint16_t *SFXNoteSet;
int16_t SFX_Counter = -1;
uint32_t duration = 0, lastNote = 0;

void SoundEngine() {
  if ( !SoundOn ) return;
  if (Game.SFX) {
    SFXNoteSet = SFXFrequencies;
    SFX = Game.SFX;
    Game.SFX = NULL;
    SFX_Counter = 2;
    lastNote = 0;
  }
  if (SFX) {
    if ( currTime < lastNote + duration ) return;
    uint8_t Packet = pgm_read_byte(SFX + SFX_Counter++);
    if (Packet == 0xFF) {
      SFX = NULL;
      SFX_Counter = -1;
      return;
    }
    uint8_t note = (Packet >> 4) & 0x0F;
    uint8_t dMultiplier = Packet & 0x0F;
    duration = pgm_read_byte(SFX) + (pgm_read_byte(SFX+1) * dMultiplier);
    uint32_t freq = ( pgm_read_word( SFXNoteSet + note - 1 ) ) / 2;
    //sound.tone( freq, duration );
    lastNote = currTime;
  }
}

void loop() {
  TitleScreen();
  Game.NewGame( );
  while ( Game.Event ) { // 0 is Off
      
    delay(1);
    currTime = millis();
    SoundEngine();
    if ( currTime > prevTime + FPSDELAY ) {
      prevTime = currTime;
      display.clear();
      kb.update();
      if (kb.getKey(2, 5).getIsPressed() || kb.getKey(1, 1).getIsPressed())       { Game.ButtonPress( ButtonJump ); }   else { Game.ButtonRelease( ButtonJump ); }
      if (kb.getKey(2, 4).getIsPressed())       { Game.ButtonPress( ButtonRun ); }    else { Game.ButtonRelease( ButtonRun ); }
      if (kb.getKey(1, 1).getIsPressed())      { Game.ButtonPress( ButtonUp ); }     else { Game.ButtonRelease( ButtonUp ); }
      if (kb.getKey(3, 1).getIsPressed())    { Game.ButtonPress( ButtonDown ); }   else { Game.ButtonRelease( ButtonDown ); }
      if (kb.getKey(2, 0).getIsPressed())    { Game.ButtonPress( ButtonLeft ); }   else { Game.ButtonRelease( ButtonLeft ); }
      if (kb.getKey(2, 2).getIsPressed())   { Game.ButtonPress( ButtonRight ); }  else { Game.ButtonRelease( ButtonRight ); }
      Game.Cycle();
            if (kb.getRisingEdgeKey() == std::make_pair(0, 0)) {
        Serial.println("uploading new software");
        //arduboy.flashlight();
        updateFromFS(SD, "/main.bin");
        rebootEspWithReason("main uploaded!!");
    }
      if ( Game.Event ) Game.Draw();
      //display.setCursor(0,0);
      //display.print(F("Score: "));
      //display.print(Game.Score);
      display.display();
    }
  }
//  display.tunes.stopScore();
  if (Game.Score) enterHighScore(1);
  displayHighScores(1);
}

//Function by nootropic design to add high scores
void enterHighScore(uint8_t file) {
  return;
  // Each block of EEPROM has 10 high scores, and each high score entry
  // is 5 uint8_ts long:  3 uint8_ts for initials and two uint8_ts for score.
  int16_t address = file * 10 * 5;
  uint8_t hi, lo;
  char initials[3];
  char tmpInitials[3];
  uint16_t tmpScore = 0;

  //if(SoundOn) sound.tones(PreChorus);
  // High score processing
  for (uint8_t i = 0; i < 10; i++) {
    hi = EEPROM.read(address + (5*i));
    lo = EEPROM.read(address + (5*i) + 1);
    if ((hi == 0xFF) && (lo == 0xFF))
    {
      // The values are uninitialized, so treat this entry
      // as a score of 0.
      tmpScore = 0;
    } else
    {
      tmpScore = (hi << 8) | lo;
    }
    if (Game.Score > tmpScore) {
      int8_t index = 0;
      initials[0] = ' ';
      initials[1] = ' ';
      initials[2] = ' ';
      Game.ActivateButtonCD();
      while (true) {  //    enterInitials();
        delay(1);
        display.clear();
        display.setCursor(16,0); display.print(F("HIGH SCORE"));
        sprintf(text, "%u", Game.Score);
        display.setCursor(88, 0); display.print(text);
        display.setCursor(56, 20); display.print(initials[0]);
        display.setCursor(64, 20); display.print(initials[1]);
        display.setCursor(72, 20); display.print(initials[2]);
        for (uint8_t i = 0; i < 3; i++) display.drawLine(56 + (i*8), 27, 56 + (i*8) + 6, 27, 1);
        display.drawLine(56, 28, 88, 28, 0);
        display.drawLine(56 + (index*8), 28, 56 + (index*8) + 6, 28, 1);
        display.display(); 
        if ( Game.ButtonOffCD() ) {
          kb.update();
          Serial.println("updating keyboard!");
          //uint8_t input = display.buttonsState();
          if (kb.getKey(2, 4).getIsPressed() || kb.getKey(2, 5).getIsPressed() ) {
            delay(2);
            index--;
            if (index < 0) index = 0;
            //else if ( SoundOn ) sound.tone(100, 50);
          }
          if (kb.getKey(2, 2).getIsPressed()) {
            delay(10);
            index++;
            if (index > 2) index = 2;
            //else if ( SoundOn ) sound.tone(100, 50);
          }
          if (kb.getKey(3, 1).getIsPressed() ) {
            delay(2);
            initials[index]++;
            //if ( SoundOn ) sound.tone(200, 50);
            // A-Z 0-9 :-? !-/ ' '
            if (initials[index] == '0') initials[index] = ' ';
            if (initials[index] == '!') initials[index] = 'A';
            if (initials[index] == '[') initials[index] = '0';
            if (initials[index] == '@') initials[index] = '!';
          }
          if (kb.getKey(1, 1).getIsPressed() ) {
            delay(2);
            initials[index]--;
            //if ( SoundOn ) sound.tone(200, 50);
            if (initials[index] == ' ') initials[index] = '?';
            if (initials[index] == '/') initials[index] = 'Z';
            if (initials[index] == 31) initials[index] = '/';
            if (initials[index] == '@') initials[index] = ' ';
          }
          if (kb.getKey(2, 4).getIsPressed()) {
            delay(2);
            if (index < 2) {
              index++;
              //if ( SoundOn ) sound.tone(200, 100);
            } else {
              //if ( SoundOn ) sound.tone(200, 100);
              break;
            }
          }
          if ( (kb.getKey(1, 1).getIsPressed() || kb.getKey(3, 1).getIsPressed() || kb.getKey(2, 4).getIsPressed() || kb.getKey(2, 5).getIsPressed() || kb.getKey(2, 0).getIsPressed() || kb.getKey(2, 2).getIsPressed()) ) Game.ActivateButtonCD();
        }
      }
      
      for(uint8_t j=i;j<10;j++) {
        hi = EEPROM.read(address + (5*j));
        lo = EEPROM.read(address + (5*j) + 1);
        if ((hi == 0xFF) && (lo == 0xFF)) tmpScore = 0;
        else tmpScore = (hi << 8) | lo;
        tmpInitials[0] = (int8_t)EEPROM.read(address + (5*j) + 2);
        tmpInitials[1] = (int8_t)EEPROM.read(address + (5*j) + 3);
        tmpInitials[2] = (int8_t)EEPROM.read(address + (5*j) + 4);

        // write score and initials to current slot
        EEPROM.write(address + (5*j), ((Game.Score >> 8) & 0xFF));
        EEPROM.write(address + (5*j) + 1, (Game.Score & 0xFF));
        EEPROM.write(address + (5*j) + 2, initials[0]);
        EEPROM.write(address + (5*j) + 3, initials[1]);
        EEPROM.write(address + (5*j) + 4, initials[2]);

        EEPROM.commit();

        // tmpScore and tmpInitials now hold what we want to
        //write in the next slot.
        Game.Score = tmpScore;
        initials[0] = tmpInitials[0];
        initials[1] = tmpInitials[1];
        initials[2] = tmpInitials[2];
      }
      return;
    }
  }
}

void displayHighScores(uint8_t file) {
  return;
  uint16_t Score;
  uint8_t y = 10;
  uint8_t x = 24;
  // Each block of EEPROM has 10 high scores, and each high score entry
  // is 5 uint8_ts long:  3 uint8_ts for initials and two uint8_ts for score.
  int16_t address = file*10*5;
  uint8_t hi, lo;
  display.clear();
  display.setCursor(25, 0);
  display.print(F("HIGH SCORES"));
  for(int16_t i = 0; i < 10; i++) {
    sprintf(text, "%2d", i+1);
    display.setCursor(x,y+(i*8));
    display.print((char *)text);
    hi = EEPROM.read(address + (5*i));
    lo = EEPROM.read(address + (5*i) + 1);
    if ((hi == 0xFF) && (lo == 0xFF)) Score = 0;
    else Score = (hi << 8) | lo;
    if (Score > 0) {
      sprintf( text, "%c%c%c %u", 
        (int8_t)EEPROM.read(address + (5*i) + 2),
        (int8_t)EEPROM.read(address + (5*i) + 3),
        (int8_t)EEPROM.read(address + (5*i) + 4),
        Score );
      display.setCursor(x + 24, y + (i*8));
      display.print((char *)text);
    }
  }
  display.display();
  Game.ActivateButtonCD();
  while ( true ) {
    delay(1);
    kb.update();
    if ((kb.getKey(1, 1).getIsPressed() || kb.getKey(3, 1).getIsPressed() || kb.getKey(2, 4).getIsPressed() || kb.getKey(2, 5).getIsPressed() || kb.getKey(2, 0).getIsPressed() || kb.getKey(2, 2).getIsPressed()) && Game.ButtonOffCD() ) return;
  }
}
