#pragma once

#include "snake.h"
#include "position.h"
#include "fruit.h"
  #include <Arduino.h>
#include "Keyboard.h"
#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

#define SPI_CLK 18
#define SPI_DATA 23
#define SPI_CS 5
#define SPI_DC 16
#define SPI_RESET 17

extern U8G2_SSD1322_NHD_256X64_F_4W_HW_SPI u8g2;

namespace Renderer {
  void initialize();
  void renderBorder();
  void renderSnake(Snake *snake);
  void renderFruit(Fruit *fruit);
  void renderGameOver(Snake *snake);
  void startFrame();
  void endFrame();
}
