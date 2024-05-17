#include "renderer.h"
#include "Arduino.h"
#include "U8g2lib.h"

#define CELL_SIZE 8
U8G2_SSD1322_NHD_256X64_F_4W_HW_SPI u8g2(U8G2_R0, SPI_CS, SPI_DC);

namespace Renderer {



  void initialize() {
    u8g2.begin();
    u8g2.setFont(u8g2_font_6x10_tf);
  }

  unsigned long time_total = 0;
  unsigned long time_last = 0;
  float framerate() {
    time_last = time_total;
    time_total = micros();
    return 1.0 / ((time_total - time_last) / 1000000.0);
  }

  void renderBorder() {
    u8g2.drawFrame(0, 0, 256, 64); 
  }
  
  void renderSnake(Snake *snake) {
    const uint8_t **body = snake->getBody();
    for(int i = 0; i < Snake::BODY_WIDTH; i++) {
      for(int j = 0; j < Snake::BODY_HEIGHT; j++) {
        if(body[i][j] > 0) {
          u8g2.drawBox(i * CELL_SIZE, j * CELL_SIZE, CELL_SIZE, CELL_SIZE);
        }
      }
    }
  }

  void renderFruit(Fruit * fruit) {
    Position position = fruit->getPosition();
    u8g2.drawFrame(position.x * CELL_SIZE + 1, position.y * CELL_SIZE + 1, CELL_SIZE - 2, CELL_SIZE - 2);
  }

  void renderGameOver(Snake *snake) {
    u8g2.drawBox(32, 20, 180, 32);
    u8g2.setDrawColor(0);
    u8g2.setCursor(34, 30);
    u8g2.print("Game Over!");
    u8g2.setCursor(34, 40);
    u8g2.print("Points: ");
    u8g2.print(snake->getPoints());
    u8g2.setCursor(34, 50);
    u8g2.print("Press any key to play again");
    u8g2.setDrawColor(1);
  }

  void startFrame() {
    u8g2.clearBuffer();
  }

  void endFrame() {
    u8g2.sendBuffer();
  }

}
