#include "Keyboard.h"
#include "snake.h"
#include "fruit.h"
#include "renderer.h"
void performUpdate(Stream &updateSource, size_t updateSize) {
    if (Update.begin(updateSize)) {      
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
    u8g2.clearBuffer();
    u8g2.sendBuffer();
    u8g2.drawButtonUTF8(128, 32, U8G2_BTN_HCENTER|U8G2_BTN_BW1, 34,  2,  3, ("writing " + path + " to ROM...").c_str());
    
    u8g2.sendBuffer();

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
Keyboard kb;

Snake snake;
Fruit fruit(&snake);

int cur, prev;
void setup() {
  Serial.begin(115200);
  uint8_t cardType;
  

   // You can uncomment this and build again
   // Serial.println("Update successfull");

   //first init and check SD card
   if (!SD.begin(4)) {
      rebootEspWithReason("Card Mount Failed");
   }

   cardType = SD.cardType();

   if (cardType == CARD_NONE) {
      rebootEspWithReason("No SD_MMC card attached");
   }
  Renderer::initialize();
  kb.init();
  cur = prev = millis();
}


void loop() {
  
  kb.update();
  if (kb.getKey(1, 1).getIsPressed()) snake.turn(UP);
  if (kb.getKey(3, 1).getIsPressed()) snake.turn(DOWN);
  if (kb.getKey(2, 0).getIsPressed()) snake.turn(LEFT);
  if (kb.getKey(2, 2).getIsPressed()) snake.turn(RIGHT);

  bool resetFruit = false;
  if(snake.nextHeadPosition() == fruit.getPosition()) {
    snake.grow();
    resetFruit = true;
  }
  cur = millis();
  if (cur - prev > 150) {
    snake.advance();
    prev = cur;
  }

  if(resetFruit) fruit.randomize(&snake);
  
  Renderer::startFrame();
  Renderer::renderBorder();
  Renderer::renderSnake(&snake);
  Renderer::renderFruit(&fruit);
  if(!snake.isAlive()) Renderer::renderGameOver(&snake);
  Renderer::endFrame();
  if (kb.getRisingEdgeKey() == std::make_pair(0, 0)) {
        Serial.println("uploading new software");
        updateFromFS(SD, "/main.bin");
        rebootEspWithReason("main uploaded!!");
    }
    if (kb.getRisingEdgeKey() != std::make_pair(-1, -1) && !snake.isAlive()) {
        rebootEspWithReason("game started again!");
    }
  

}
