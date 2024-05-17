/**
 * TetriZimoslaw by Jakub Niewiarowski 2022
 * 
 * Tetriz for Arduino Uno and 128x64 px monochrome LCD
 * 
 */

#include <Arduino.h>
#include <EEPROM.h>
#include <U8g2lib.h>
#include <memory.h>
#include "Keyboard.h"

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
U8G2_SSD1322_NHD_256X64_F_4W_HW_SPI u8g2(U8G2_R0, SPI_CS, SPI_DC);

Keyboard kb;
byte y = 1 /*block coordinate on Y axis (top of the screen to bottom)*/,
  x = 4 /*block coordinate on X axis (from left to right)*/,
  shape = 0 /*ID of current block (shape)
    0 = O (square)
    1 = Z
    2 = S
    3 = L
    4 = J (inverted L)
    5 = I
  */,
  nextShape = 0 /*ID of next block (shape)*/,
  rotation = 0 /*ID of current block's rotation
    0 = 
    1 =
    2 = 
    3 =
  */,
  lvl = 1 /*current level (higher level = higher speed of falling)*/,
  lines = 0 /*number of cleared lines*/,
  s = 100 /*falling speed (changes when soft dropping)*/,
  lastI = 0 /*how many blocks, other than I, was drawn since last I block was drawn*/,
  prevSCounter = 0 /*how many block of the same shape were in a row*/;
unsigned int cycle = 0; /*number of cycles. Used for time keeping*/
unsigned long score = 0; /*player's score*/
bool bricks[10][21] /*coordinate system for bricks. True = display a brick on coordinates given in bricks[x][y]*/,
  input = false; /*is any input received from user*/

//----------------------------Game Over screen--------------------------
void gameOver()
{
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_courB08_tf);
  u8g2.drawStr(5,50,"GAME OVER");
  u8g2.setFont(u8g2_font_micro_tr);
  u8g2.drawStr(20,60,"SCORE:");
  u8g2.setCursor(14, 68);
  u8g2.print(score);
  u8g2.drawStr(10,80,"BEST SCORE:");
  u8g2.setCursor(14, 88);
  unsigned long bestScore = 0;
  for(int i=0; i<4; i++)
     bestScore += EEPROM.read(i)*pow(256,3-i);
  u8g2.print(bestScore);
  if(score > bestScore)
  {
    for(int i=0; i<4; i++)
    {
      unsigned long x = floor(score/pow(256,3-i));
      EEPROM.write(i,x);
      score -= x*pow(256,3-i);
    }
      
    u8g2.drawStr(3,120,"NEW BEST SCORE!");
  }
  u8g2.drawStr(20,100,"LINES:");
  u8g2.setCursor(26, 108);
  u8g2.print(lines);
  u8g2.sendBuffer();
  delay(1000);
  memset(bricks, false, sizeof(bricks));
}

//-----------------------------Pause screen-----------------------------
void pausegame()
{
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_courB08_tf);
  u8g2.drawStr(16,60,"PAUSED");
  u8g2.setFont(u8g2_font_micro_tr);
  u8g2.sendBuffer();
  delay(1000);
  while(true)
  {
    if(kb.getKey(0, 1).getIsPressed() || kb.getKey(2, 1).getIsPressed())
      break;
  }
}

//--------------Checking if block can fall (move 1 unit down)----------
bool checkShape(byte x, byte y, byte d)
{
  switch(shape)
  {
    case 0: // O
      switch(d)
      {
        case 0: //na dół
          if(!bricks[x][y+1] && !bricks[x-1][y+1])
            return true;
          else
            return false;  
        break;
        case 1: //w prawo
          if(!bricks[x+1][y] && !bricks[x+1][y-1])
            return true;
          else
            return false;  
        break;
        case 2: //w lewo
          if(!bricks[x-2][y] && !bricks[x-2][y-1] && x > 1)
            return true;
          else
            return false;  
        break;
      }
    break;


    case 1: // Z
      switch(rotation)
      {
        case 0:
          switch(d)
          {
            case 0: //w dół
              if(!bricks[x][y+1] && !bricks[x+1][y+1] && !bricks[x-1][y])
                return true;
              else
                return false;
            break;
            case 1: //w prawo
              if(!bricks[x+2][y] && !bricks[x+1][y-1] && x < 8)
                return true;
              else
                return false;
            break;
            case 2: //w lewo
              if(!bricks[x-1][y] && !bricks[x-2][y-1] && x > 1)
                return true;
              else
                return false;
            break;
            case 3: //rotacja w prawo
              if(!bricks[x+1][y-1] && !bricks[x][y+1])
                return true;
              else
                return false;
            break;
            case 4: //rotacja w lewo
              if(!bricks[x+1][y-1] && !bricks[x][y+1])
                return true;
              else
                return false;
            break;
          }
        break;
        
        case 1: // o jeden w prawo
          switch(d)
          {
            case 0: //w dół
              if(!bricks[x][y+2] && !bricks[x+1][y+1] && y < 18)
                return true;
              else
                return false;
            break;
            case 1: //w prawo
              if(!bricks[x+2][y] && !bricks[x+1][y+1] && !bricks[x+2][y-1] && x < 8)
                return true;
              else
                return false;
            break;
            case 2: //w lewo
              if(!bricks[x-1][y] && !bricks[x-1][y+1] && !bricks[x][y-1])
                return true;
              else
                return false;
            break;
            case 3: //rotacja w prawo
              if(!bricks[x][y-1] && !bricks[x-1][y-1] && x > 0)
                return true;
              else
                return false;
            break;
            case 4: //rotacja w lewo
              if(!bricks[x][y-1] && !bricks[x-1][y-1] && x > 0)
                return true;
              else
                return false;
            break;
          } 
        break;
        
        case 2: // o dwa (taki sam jak 0)
          switch(d)
          {
            case 0: //w dół
              if(!bricks[x][y+1] && !bricks[x+1][y+1] && !bricks[x-1][y])
                return true;
              else
                return false;
            break;
            case 1: //w prawo
              if(!bricks[x+2][y] && !bricks[x+1][y-1] && x < 8)
                return true;
              else
                return false;
            break;
            case 2: //w lewo
              if(!bricks[x-1][y] && !bricks[x-2][y-1] && x > 1)
                return true;
              else
                return false;
            break;
            case 3: //rotacja w prawo
              if(!bricks[x+1][y-1] && !bricks[x][y+1])
                return true;
              else
                return false;
            break;
            case 4: //rotacja w lewo
              if(!bricks[x+1][y-1] && !bricks[x][y+1])
                return true;
              else
                return false;
            break;
          }
        break;
        
        case 3: // o jeden w lewo (taki sam jak 1)
          switch(d)
          {
            case 0: //w dół
              if(!bricks[x][y+2] && !bricks[x+1][y+1] && y < 18)
                return true;
              else
                return false;
            break;
            case 1: //w prawo
              if(!bricks[x+2][y] && !bricks[x+1][y+1] && !bricks[x+2][y-1] && x < 8)
                return true;
              else
                return false;
            break;
            case 2: //w lewo
              if(!bricks[x-1][y] && !bricks[x-1][y+1] && !bricks[x][y-1])
                return true;
              else
                return false;
            break;
            case 3: //rotacja w prawo
              if(!bricks[x][y-1] && !bricks[x-1][y-1] && x > 0)
                return true;
              else
                return false;
            break;
            case 4: //rotacja w lewo
              if(!bricks[x][y-1] && !bricks[x-1][y-1] && x > 0)
                return true;
              else
                return false;
            break;
          }
        break;
      }
    break;


    case 2: // S
      switch(rotation)
      {
        case 0:
          switch(d)
          {
            case 0: //w dół
              if(!bricks[x][y+1] && !bricks[x-1][y+1] && !bricks[x+1][y])
                return true;
              else
                return false;
            break;
            case 1: //w prawo
              if(!bricks[x+1][y] && !bricks[x+2][y-1] && x < 8)
                return true;
              else
                return false;
            break;
            case 2: //w lewo
              if(!bricks[x-2][y] && !bricks[x-1][y-1] && x > 1)
                return true;
              else
                return false;
            break;
            case 3: //rotacja w prawo
              if(!bricks[x-1][y-1] && !bricks[x][y+1])
                return true;
              else
                return false;
            break;
            case 4: //rotacja w lewo
              if(!bricks[x-1][y-1] && !bricks[x][y+1])
                return true;
              else
                return false;
            break;
          }
        break;
        
        case 1: // o jeden w prawo
          switch(d)
          {
            case 0: //w dół
              if(!bricks[x][y+2] && !bricks[x-1][y+1])
                return true;
              else
                return false;
            break;
            case 1: //w prawo
              if(!bricks[x+1][y] && !bricks[x][y-1] && !bricks[x+1][y+1] && x < 9)
                return true;
              else
                return false;
            break;
            case 2: //w lewo
              if(!bricks[x-2][y] && !bricks[x-2][y-1] && !bricks[x-1][y+1] && x > 1)
                return true;
              else
                return false;
            break;
            case 3: //rotacja w prawo
              if(!bricks[x][y-1] && !bricks[x+1][y-1] && x < 9)
                return true;
              else
                return false;
            break;
            case 4: //rotacja w lewo
              if(!bricks[x][y-1] && !bricks[x+1][y-1] && x < 9)
                return true;
              else
                return false;
            break;
          } 
        break;
        
        case 2: // o dwa (taki sam jak 0)
          switch(d)
          {
            case 0: //w dół
              if(!bricks[x][y+1] && !bricks[x-1][y+1] && !bricks[x+1][y])
                return true;
              else
                return false;
            break;
            case 1: //w prawo
              if(!bricks[x+1][y] && !bricks[x+2][y-1] && x < 8)
                return true;
              else
                return false;
            break;
            case 2: //w lewo
              if(!bricks[x-2][y] && !bricks[x-1][y-1] && x > 1)
                return true;
              else
                return false;
            break;
            case 3: //rotacja w prawo
              if(!bricks[x-1][y-1] && !bricks[x][y+1])
                return true;
              else
                return false;
            break;
            case 4: //rotacja w lewo
              if(!bricks[x-1][y-1] && !bricks[x][y+1])
                return true;
              else
                return false;
            break;
          }
        break;
        
        case 3: // o jeden w lewo (taki sam jak 1)
          switch(d)
          {
            case 0: //w dół
              if(!bricks[x][y+2] && !bricks[x-1][y+1])
                return true;
              else
                return false;
            break;
            case 1: //w prawo
              if(!bricks[x+1][y] && !bricks[x][y-1] && !bricks[x+1][y+1] && x < 9)
                return true;
              else
                return false;
            break;
            case 2: //w lewo
              if(!bricks[x-2][y] && !bricks[x-2][y-1] && !bricks[x-1][y+1] && x > 1)
                return true;
              else
                return false;
            break;
            case 3: //rotacja w prawo
              if(!bricks[x][y+1] && !bricks[x+1][y+1] && x < 9)
                return true;
              else
                return false;
            break;
            case 4: //rotacja w lewo
              if(!bricks[x][y+1] && !bricks[x+1][y+1] && x < 9)
                return true;
              else
                return false;
            break;
          }
        break;
      }
    break;


    case 3: // L
      switch(rotation)
      {
        case 0:
          switch(d)
          {
            case 0: //w dół
              if(!bricks[x][y+1] && !bricks[x+1][y+1])
                return true;
              else
                return false;
            break;
            case 1: //w prawo
              if(!bricks[x+2][y] && !bricks[x+1][y-1] && !bricks[x+1][y-2] && x < 8)
                return true;
              else
                return false;
            break;
            case 2: //w lewo
              if(!bricks[x-1][y] && !bricks[x-1][y-1] && !bricks[x-1][y-2] && x > 0)
                return true;
              else
                return false;
            break;
            case 3: //rotacja w prawo
              if(!bricks[x+2][y] && !bricks[x][y+1] && x < 8)
                return true;
              else
                return false;
            break;
            case 4: //rotacja w lewo
              if(!bricks[x-1][y] && !bricks[x-2][y] && x > 1)
                return true;
              else
                return false;
            break;
          }
        break;
        
        case 1: // o jeden w prawo
          switch(d)
          {
            case 0: //w dół
              if(!bricks[x][y+2] && !bricks[x+1][y+1] && !bricks[x+2][y+1])
                return true;
              else
                return false;
            break;
            case 1: //w prawo
              if(!bricks[x+3][y] && !bricks[x+1][y+1] && x < 7)
                return true;
              else
                return false;
            break;
            case 2: //w lewo
              if(!bricks[x-1][y] && !bricks[x-1][y+1])
                return true;
              else
                return false;
            break;
            case 3: //rotacja w prawo
              if(!bricks[x][y+2] && !bricks[x-1][y-1] && x > 0)
                return true;
              else
                return false;
            break;
            case 4: //rotacja w lewo
              if(!bricks[x][y-1] && !bricks[x][y-2])
                return true;
              else
                return false;
            break;
          } 
        break;
        
        case 2: // o dwa
          switch(d)
          {
            case 0: //w dół
              if(!bricks[x][y+3] && !bricks[x-1][y+1] )
                return true;
              else
                return false;
            break;
            case 1: //w prawo
              if(!bricks[x+1][y] && !bricks[x+1][y+1] && !bricks[x+1][y+2] )
                return true;
              else
                return false;
            break;
            case 2: //w lewo
              if(!bricks[x-2][y] && !bricks[x-1][y+1] && !bricks[x-1][y+2] && x > 1)
                return true;
              else
                return false;
            break;
            case 3: //rotacja w prawo
              if(!bricks[x][y-1] && !bricks[x-2][y] && x > 1)
                return true;
              else
                return false;
            break;
            case 4: //rotacja w lewo
              if(!bricks[x+1][y] && !bricks[x+2][y] && x < 8)
                return true;
              else
                return false;
            break;
          }
        break;
        
        case 3: // o jeden w lewo
          switch(d)
          {
            case 0: //w dół
              if(!bricks[x][y+1] && !bricks[x-1][y+1] && !bricks[x-2][y+1])
                return true;
              else
                return false;
            break;
            case 1: //w prawo
              if(!bricks[x+1][y] && !bricks[x+1][y-1])
                return true;
              else
                return false;
            break;
            case 2: //w lewo
              if(!bricks[x-3][y] && !bricks[x-1][y-1] && x > 2)
                return true;
              else
                return false;
            break;
            case 3: //rotacja w prawo
              if(!bricks[x+1][y] && !bricks[x][y-2] && x < 9)
                return true;
              else
                return false;
            break;
            case 4: //rotacja w lewo
              if(!bricks[x][y+1] && !bricks[x][y+2])
                return true;
              else
                return false;
            break;
          }
        break;
      }
    break;


    case 4: // J
      switch(rotation)
      {
        case 0:
          switch(d)
          {
            case 0: //w dół
              if(!bricks[x][y+1] && !bricks[x-1][y+1])
                return true;
              else
                return false;
            break;
            case 1: //w prawo
              if(!bricks[x+1][y] && !bricks[x+1][y-1] && !bricks[x+1][y-2])
                return true;
              else
                return false;
            break;
            case 2: //w lewo
              if(!bricks[x-2][y] && !bricks[x-1][y-1] && !bricks[x-1][y-2] && x > 1)
                return true;
              else
                return false;
            break;
            case 3: //rotacja w prawo
              if(!bricks[x+1][y] && !bricks[x+2][y] && x < 8)
                return true;
              else
                return false;
            break;
            case 4: //rotacja w lewo
              if(!bricks[x][y+1] && !bricks[x-2][y] && x > 1)
                return true;
              else
                return false;
            break;
          }
        break;
        
        case 1: // o jeden w prawo
          switch(d)
          {
            case 0: //w dół
              if(!bricks[x][y+1] && !bricks[x+1][y+1] && !bricks[x+2][y+1])
                return true;
              else
                return false;
            break;
            case 1: //w prawo
              if(!bricks[x+3][y] && !bricks[x+1][y-1] && x < 7)
                return true;
              else
                return false;
            break;
            case 2: //w lewo
              if(!bricks[x-1][y] && !bricks[x-1][y-1])
                return true;
              else
                return false;
            break;
            case 3: //rotacja w prawo
              if(!bricks[x][y+1] && !bricks[x][y+2])
                return true;
              else
                return false;
            break;
            case 4: //rotacja w lewo
              if(!bricks[x-1][y] && !bricks[x][y-2] && x > 0)
                return true;
              else
                return false;
            break;
          } 
        break;
        
        case 2: // o dwa
          switch(d)
          {
            case 0: //w dół
              if(!bricks[x][y+3] && !bricks[x+1][y+1] )
                return true;
              else
                return false;
            break;
            case 1: //w prawo
              if(!bricks[x+2][y] && !bricks[x+1][y+1] && !bricks[x+1][y+2] && x < 8)
                return true;
              else
                return false;
            break;
            case 2: //w lewo
              if(!bricks[x-1][y] && !bricks[x-1][y+1] && !bricks[x-1][y+2])
                return true;
              else
                return false;
            break;
            case 3: //rotacja w prawo
              if(!bricks[x-1][y] && !bricks[x-2][y] && x > 1)
                return true;
              else
                return false;
            break;
            case 4: //rotacja w lewo
              if(!bricks[x][y-1] && !bricks[x+2][y] && x < 8)
                return true;
              else
                return false;
            break;
          }
        break;
        
        case 3: // o jeden w lewo
          switch(d)
          {
            case 0: //w dół
              if(!bricks[x][y+2] && !bricks[x-1][y+1] && !bricks[x-2][y+1])
                return true;
              else
                return false;
            break;
            case 1: //w prawo
              if(!bricks[x+1][y] && !bricks[x+1][y+1])
                return true;
              else
                return false;
            break;
            case 2: //w lewo
              if(!bricks[x-3][y] && !bricks[x-1][y+1] && x > 2)
                return true;
              else
                return false;
            break;
            case 3: //rotacja w prawo
              if(!bricks[x][y-1] && !bricks[x][y-2])
                return true;
              else
                return false;
            break;
            case 4: //rotacja w lewo
              if(!bricks[x+1][y] && !bricks[x][y+2] && x < 9)
                return true;
              else
                return false;
            break;
          }
        break;
      }
    break;


    case 5: // T
      switch(rotation)
      {
        case 0:
          switch(d)
          {
            case 0: //w dół
              if(!bricks[x][y+1] && !bricks[x-1][y+1] && !bricks[x+1][y+1])
                return true;
              else
                return false;
            break;
            case 1: //w prawo
              if(!bricks[x+2][y] && !bricks[x+1][y-1] && x < 8)
                return true;
              else
                return false;
            break;
            case 2: //w lewo
              if(!bricks[x-2][y] && !bricks[x-1][y-1] && x > 1)
                return true;
              else
                return false;
            break;
            case 3: //rotacja w prawo
              if(!bricks[x][y+1])
                return true;
              else
                return false;
            break;
            case 4: //rotacja w lewo
              if(!bricks[x][y+1])
                return true;
              else
                return false;
            break;
          }
        break;
        
        case 1: // o jeden w prawo
          switch(d)
          {
            case 0: //w dół
              if(!bricks[x][y+2] && !bricks[x+1][y+1])
                return true;
              else
                return false;
            break;
            case 1: //w prawo
              if(!bricks[x+2][y] && !bricks[x+1][y-1] && !bricks[x+1][y+1] && x < 8)
                return true;
              else
                return false;
            break;
            case 2: //w lewo
              if(!bricks[x-1][y] && !bricks[x-1][y-1] && !bricks[x-1][y+1])
                return true;
              else
                return false;
            break;
            case 3: //rotacja w prawo
              if(!bricks[x-1][y] && x > 0)
                return true;
              else
                return false;
            break;
            case 4: //rotacja w lewo
              if(!bricks[x-1][y] && x > 0)
                return true;
              else
                return false;
            break;
          } 
        break;
        
        case 2: // o dwa
          switch(d)
          {
            case 0: //w dół
              if(!bricks[x][y+2] && !bricks[x+1][y+1] && !bricks[x-1][y+1])
                return true;
              else
                return false;
            break;
            case 1: //w prawo
              if(!bricks[x+2][y] && !bricks[x+1][y+1] && x < 8)
                return true;
              else
                return false;
            break;
            case 2: //w lewo
              if(!bricks[x-2][y] && !bricks[x-1][y+1] && x > 1)
                return true;
              else
                return false;
            break;
            case 3: //rotacja w prawo
              if(!bricks[x][y-1])
                return true;
              else
                return false;
            break;
            case 4: //rotacja w lewo
              if(!bricks[x][y-1])
                return true;
              else
                return false;
            break;
          }
        break;
        
        case 3: // o jeden w lewo
          switch(d)
          {
            case 0: //w dół
              if(!bricks[x][y+2] && !bricks[x-1][y+1])
                return true;
              else
                return false;
            break;
            case 1: //w prawo
              if(!bricks[x+1][y] && !bricks[x+1][y+1] && !bricks[x+1][y-1])
                return true;
              else
                return false;
            break;
            case 2: //w lewo
              if(!bricks[x-2][y] && !bricks[x-1][y+1] && !bricks[x-1][y-1] && x > 1)
                return true;
              else
                return false;
            break;
            case 3: //rotacja w prawo
              if(!bricks[x+1][y] && x < 9)
                return true;
              else
                return false;
            break;
            case 4: //rotacja w lewo
              if(!bricks[x+1][y] && x < 9)
                return true;
              else
                return false;
            break;
          }
        break;
      }
    break;

    case 6: // I
      switch(rotation)
      {
        case 0:
          switch(d)
          {
            case 0: //w dół
              if(!bricks[x][y+2])
                return true;
              else
                return false;
            break;
            case 1: //w prawo
              if(!bricks[x+1][y] && !bricks[x+1][y-1] && !bricks[x+1][y+1] && !bricks[x+1][y-2])
                return true;
              else
                return false;
            break;
            case 2: //w lewo
              if(!bricks[x-1][y] && !bricks[x-1][y-1] && !bricks[x-1][y+1] && !bricks[x-1][y-2])
                return true;
              else
                return false;
            break;
            case 3: //rotacja w prawo
              if(!bricks[x+1][y] && !bricks[x+2][y] && !bricks[x-1][y] && x < 8 && x > 0)
                return true;
              else
                return false;
            break;
            case 4: //rotacja w lewo
              if(!bricks[x+1][y] && !bricks[x-2][y] && !bricks[x-1][y] && x < 9 && x > 1)
                return true;
              else
                return false;
            break;
          }
        break;
        
        case 1: // o jeden w prawo
          switch(d)
          {
            case 0: //w dół
              if(!bricks[x-1][y+1] && !bricks[x][y+1] && !bricks[x+1][y+1] && !bricks[x+2][y+1])
                return true;
              else
                return false;
            break;
            case 1: //w prawo
              if(!bricks[x+3][y] && x < 7)
                return true;
              else
                return false;
            break;
            case 2: //w lewo
              if(!bricks[x-2][y] && x > 1)
                return true;
              else
                return false;
            break;
            case 3: //rotacja w prawo
              if(!bricks[x][y-1] && !bricks[x][y+1] && !bricks[x][y+2])
                return true;
              else
                return false;
            break;
            case 4: //rotacja w lewo
              if(!bricks[x][y-1] && !bricks[x][y+1] && !bricks[x][y-2])
                return true;
              else
                return false;
            break;
          } 
        break;
        
        case 2: // o dwa
          switch(d)
          {
            case 0: //w dół
              if(!bricks[x][y+3])
                return true;
              else
                return false;
            break;
            case 1: //w prawo
              if(!bricks[x+1][y] && !bricks[x+1][y-1] && !bricks[x+1][y+1] && !bricks[x+1][y+2])
                return true;
              else
                return false;
            break;
            case 2: //w lewo
              if(!bricks[x-1][y] && !bricks[x-1][y-1] && !bricks[x-1][y+1] && !bricks[x-1][y+2])
                return true;
              else
                return false;
            break;
            case 3: //rotacja w prawo
              if(!bricks[x+1][y] && !bricks[x-2][y] && !bricks[x-1][y] && x < 9 && x > 1)
                return true;
              else
                return false;
            break;
            case 4: //rotacja w lewo
              if(!bricks[x-1][y] && !bricks[x+2][y] && !bricks[x+1][y] && x < 8 && x > 0)
                return true;
              else
                return false;
            break;
          }
        break;
        
        case 3: // o jeden w lewo
          switch(d)
          {
            case 0: //w dół
              if(!bricks[x+1][y+1] && !bricks[x][y+1] && !bricks[x-1][y+1] && !bricks[x-2][y+1])
                return true;
              else
                return false;
            break;
            case 1: //w prawo
              if(!bricks[x+2][y] && x < 8)
                return true;
              else
                return false;
            break;
            case 2: //w lewo
              if(!bricks[x-3][y] && x > 2)
                return true;
              else
                return false;
            break;
            case 3: //rotacja w prawo
              if(!bricks[x][y-1] && !bricks[x][y-2] && !bricks[x][y+1])
                return true;
              else
                return false;
            break;
            case 4: //rotacja w lewo
              if(!bricks[x][y-1] && !bricks[x][y+1] && !bricks[x][y+2])
                return true;
              else
                return false;
            break;
          } 
        break;;
      }
    break;
  }
}

//----------------------Removing block from matrix-----------------------
void clearShape(byte x, byte y)
{
  switch(shape)
  {
    case 0: // O
      bricks[x][y] = false; //prawy dolny
      bricks[x][y-1] = false; //prawy górny
      bricks[x-1][y] = false; //lewy dolny
      bricks[x-1][y-1] = false; //lewy górny
    break;

    case 1: // Z
      switch(rotation)
      {
        case 0:
          bricks[x][y] = false; //dolny środkowy
          bricks[x+1][y] = false; //dolny prawy
          bricks[x][y-1] = false; //górny środkowy 
          bricks[x-1][y-1] = false; //górny lewy
        break;
        case 1: // o jeden w prawo
          bricks[x][y+1] = false; //dolny lewy
          bricks[x][y] = false; //środkowy lewy
          bricks[x+1][y] = false; //środkowy prawy
          bricks[x+1][y-1] = false; //górny prawy
        break;
        case 2: // o dwa (taki sam jak 0)
          bricks[x][y] = false; //dolny środkowy
          bricks[x+1][y] = false; //dolny prawy
          bricks[x][y-1] = false; //górny środkowy 
          bricks[x-1][y-1] = false; //górny lewy
        break;
        case 3: // o jeden w lewo (taki sam jak 1)
          bricks[x][y+1] = false; //środkowy lewy
          bricks[x][y] = false; //dolny lewy
          bricks[x+1][y] = false; //środkowy prawy
          bricks[x+1][y-1] = false; //górny prawy
        break;
      }
    break;

    case 2: // S
      switch(rotation)
      {
        case 0:
          bricks[x][y] = false; //dolny środkowy
          bricks[x-1][y] = false; //dolny lewy
          bricks[x][y-1] = false; //górny środkowy 
          bricks[x+1][y-1] = false; //górny prawy
        break;
        case 1: // o jeden w prawo
          bricks[x-1][y] = false; //środkowy lewy
          bricks[x-1][y-1] = false; //górny lewy
          bricks[x][y] = false; //środkowy prawy
          bricks[x][y+1] = false; //dolny prawy 
        break;
        case 2: // o dwa (taki sam jak 0)
          bricks[x][y] = false; //dolny środkowy
          bricks[x-1][y] = false; //dolny lewy
          bricks[x][y-1] = false; //górny środkowy 
          bricks[x+1][y-1] = false; //górny prawy
        break;
        case 3: // o jeden w lewo (taki sam jak 1)
          bricks[x-1][y] = false; //środkowy lewy
          bricks[x-1][y-1] = false; //górny lewy
          bricks[x][y] = false; //środkowy prawy
          bricks[x][y+1] = false; //dolny prawy 
        break;
      }
    break;

    case 3: // L
      switch(rotation)
      {
        case 0:
          bricks[x][y] = false; //dolny środkowy
          bricks[x+1][y] = false; //dolny prawy
          bricks[x][y-1] = false; //środkowy środkowy 
          bricks[x][y-2] = false; //górny środkowy 
        break;
        case 1: // o jeden w prawo
          bricks[x][y] = false; //górny lewy
          bricks[x][y+1] = false; //dolny lewy
          bricks[x+1][y] = false; //górny środkowy
          bricks[x+2][y] = false; //dolny prawy 
        break;
        case 2: // o dwa
          bricks[x][y] = false; //górny prawy
          bricks[x-1][y] = false; //górny lewy
          bricks[x][y+1] = false; //środkowy prawy
          bricks[x][y+2] = false; //dolny prawy
        break;
        case 3: // o jeden w lewo
          bricks[x][y] = false; //dolny prawy
          bricks[x][y-1] = false; //górny prawy
          bricks[x-1][y] = false; //dolny środkowy
          bricks[x-2][y] = false; // dolny lewy
        break;
      }
    break;

    case 4: // J
      switch(rotation)
      {
        case 0:
          bricks[x][y] = false; //dolny prawy
          bricks[x-1][y] = false; //dolny lewy
          bricks[x][y-1] = false; //środkowy prawy
          bricks[x][y-2] = false; //górny prawy
        break;
        case 1: // o jeden w prawo
          bricks[x][y-1] = false; //górny lewy
          bricks[x][y] = false; //dolny lewy
          bricks[x+1][y] = false; //dolny środkowy
          bricks[x+2][y] = false; //dolny prawy 
        break;
        case 2: // o dwa
          bricks[x][y] = false; //górny lewy
          bricks[x+1][y] = false; //górny prawy
          bricks[x][y+1] = false; //środkowy lewy
          bricks[x][y+2] = false; //dolny lewy
        break;
        case 3: // o jeden w lewo
          bricks[x][y] = false; //górny prawy
          bricks[x][y+1] = false; //dolny prawy
          bricks[x-1][y] = false; //górny środkowy
          bricks[x-2][y] = false; // górny lewy
        break;
      }
    break;

    case 5: // T
      switch(rotation)
      {
        case 0:
          bricks[x][y] = false; //dolny środkowy
          bricks[x-1][y] = false; //dolny lewy
          bricks[x+1][y] = false; //dolny prawy
          bricks[x][y-1] = false; //górny środkowy
        break;
        case 1: // o jeden w prawo
          bricks[x][y-1] = false; //górny lewy
          bricks[x][y] = false; //środkowy lewy
          bricks[x+1][y] = false; //środkowy prawy
          bricks[x][y+1] = false; //dolny lewy
        break;
        case 2: // o dwa
          bricks[x][y] = false; //górny środkowy
          bricks[x+1][y] = false; //górny prawy
          bricks[x][y+1] = false; //dolny środkowy
          bricks[x-1][y] = false; //górny lewy
        break;
        case 3: // o jeden w lewo
          bricks[x][y-1] = false; //górny prawy
          bricks[x][y] = false; //środkowy prawy
          bricks[x-1][y] = false; //środkowy lewy
          bricks[x][y+1] = false; //dolny prawy
        break;
      }
    break;

    case 6: // I
      switch(rotation)
      {
        case 0:
          bricks[x][y+1] = false; //1 od dołu
          bricks[x][y] = false; //2 od dołu
          bricks[x][y-1] = false; //3 od dołu
          bricks[x][y-2] = false; //4 od dołu
        break;
        case 1: // o jeden w prawo
          bricks[x-1][y] = false; //1 od lewej
          bricks[x][y] = false; //2 od lewej
          bricks[x+1][y] = false; //3 od lewej
          bricks[x+2][y] = false; //4 od lewej
        break;
        case 2: // o dwa
          bricks[x][y+2] = false; //1 od dołu
          bricks[x][y+1] = false; //2 od dołu
          bricks[x][y] = false; //3 od dołu
          bricks[x][y-1] = false; //4 od dołu
        break;
        case 3: // o jeden w lewo
          bricks[x-2][y] = false; //1 od lewej
          bricks[x-1][y] = false; //2 od lewej
          bricks[x][y] = false; //3 od lewej
          bricks[x+1][y] = false; //4 od lewej
        break;
      }
    break;
  }
}

//-----------------Putting block on matrix------------------------------
void drawShape(byte x, byte y)
{
  switch(shape)
  {
    case 0: // O 
      bricks[x][y] = true; //prawy dolny
      bricks[x][y-1] = true; //prawy górny
      bricks[x-1][y] = true; //lewy dolny
      bricks[x-1][y-1] = true; //lewy górny
    break;
    
    case 1: // Z
      switch(rotation)
      {
        case 0:
          bricks[x][y] = true; //dolny środkowy
          bricks[x+1][y] = true; //dolny prawy
          bricks[x][y-1] = true; //górny środkowy 
          bricks[x-1][y-1] = true; //górny lewy 
        break;
        case 1: // o jeden w prawo
          bricks[x][y+1] = true; //środkowy lewy
          bricks[x][y] = true; //dolny lewy
          bricks[x+1][y] = true; //środkowy prawy
          bricks[x+1][y-1] = true; //górny prawy 
        break;
        case 2: // o dwa (taki sam jak 0)
          bricks[x][y] = true; //dolny środkowy
          bricks[x+1][y] = true; //dolny prawy
          bricks[x][y-1] = true; //górny środkowy 
          bricks[x-1][y-1] = true; //górny lewy 
        break;
        case 3: // o jeden w lewo (taki sam jak 1)
          bricks[x][y+1] = true; //środkowy lewy
          bricks[x][y] = true; //dolny lewy
          bricks[x+1][y] = true; //środkowy prawy
          bricks[x+1][y-1] = true; //górny prawy 
        break;
      }
    break;
    
    case 2: // S
      switch(rotation)
      {
        case 0:
          bricks[x][y] = true; //dolny środkowy
          bricks[x-1][y] = true; //dolny lewy
          bricks[x][y-1] = true; //górny środkowy 
          bricks[x+1][y-1] = true; //górny prawy
        break;
        case 1: // o jeden w prawo
          bricks[x-1][y] = true; //środkowy lewy
          bricks[x-1][y-1] = true; //górny lewy
          bricks[x][y] = true; //środkowy prawy
          bricks[x][y+1] = true; //dolny prawy 
        break;
        case 2: // o dwa (taki sam jak 0)
          bricks[x][y] = true; //dolny środkowy
          bricks[x-1][y] = true; //dolny lewy
          bricks[x][y-1] = true; //górny środkowy 
          bricks[x+1][y-1] = true; //górny prawy
        break;
        case 3: // o jeden w lewo (taki sam jak 1)
          bricks[x-1][y] = true; //środkowy lewy
          bricks[x-1][y-1] = true; //górny lewy
          bricks[x][y] = true; //środkowy prawy
          bricks[x][y+1] = true; //dolny prawy 
        break;
      }
    break;

    case 3: // L
      switch(rotation)
      {
        case 0:
          bricks[x][y] = true; //dolny lewy
          bricks[x+1][y] = true; //dolny prawy
          bricks[x][y-1] = true; //środkowy lewy
          bricks[x][y-2] = true; //górny lewy 
        break;
        case 1: // o jeden w prawo
          bricks[x][y] = true; //górny lewy
          bricks[x][y+1] = true; //dolny lewy
          bricks[x+1][y] = true; //górny środkowy
          bricks[x+2][y] = true; //dolny prawy 
        break;
        case 2: // o dwa
          bricks[x][y] = true; //górny prawy
          bricks[x-1][y] = true; //górny lewy
          bricks[x][y+1] = true; //środkowy prawy
          bricks[x][y+2] = true; //dolny prawy
        break;
        case 3: // o jeden w lewo
          bricks[x][y] = true; //dolny prawy
          bricks[x][y-1] = true; //górny prawy
          bricks[x-1][y] = true; //dolny środkowy
          bricks[x-2][y] = true; // dolny lewy
        break;
      }
    break;

    case 4: // J
      switch(rotation)
      {
        case 0:
          bricks[x][y] = true; //dolny prawy
          bricks[x-1][y] = true; //dolny lewy
          bricks[x][y-1] = true; //środkowy prawy
          bricks[x][y-2] = true; //górny prawy
        break;
        case 1: // o jeden w prawo
          bricks[x][y-1] = true; //górny lewy
          bricks[x][y] = true; //dolny lewy
          bricks[x+1][y] = true; //dolny środkowy
          bricks[x+2][y] = true; //dolny prawy 
        break;
        case 2: // o dwa
          bricks[x][y] = true; //górny lewy
          bricks[x+1][y] = true; //górny prawy
          bricks[x][y+1] = true; //środkowy lewy
          bricks[x][y+2] = true; //dolny lewy
        break;
        case 3: // o jeden w lewo
          bricks[x][y] = true; //górny prawy
          bricks[x][y+1] = true; //dolny prawy
          bricks[x-1][y] = true; //górny środkowy
          bricks[x-2][y] = true; // górny lewy
        break;
      }
    break;

    case 5: // T
      switch(rotation)
      {
        case 0:
          bricks[x][y] = true; //dolny środkowy
          bricks[x-1][y] = true; //dolny lewy
          bricks[x+1][y] = true; //dolny prawy
          bricks[x][y-1] = true; //górny środkowy
        break;
        case 1: // o jeden w prawo
          bricks[x][y-1] = true; //górny lewy
          bricks[x][y] = true; //środkowy lewy
          bricks[x+1][y] = true; //środkowy prawy
          bricks[x][y+1] = true; //dolny lewy
        break;
        case 2: // o dwa
          bricks[x][y] = true; //górny środkowy
          bricks[x+1][y] = true; //górny prawy
          bricks[x][y+1] = true; //dolny środkowy
          bricks[x-1][y] = true; //górny lewy
        break;
        case 3: // o jeden w lewo
          bricks[x][y-1] = true; //górny prawy
          bricks[x][y] = true; //środkowy prawy
          bricks[x-1][y] = true; //środkowy lewy
          bricks[x][y+1] = true; //dolny prawy
        break;
      }
    break;

    case 6: // I
      switch(rotation)
      {
        case 0:
          bricks[x][y+1] = true; //1 od dołu
          bricks[x][y] = true; //2 od dołu
          bricks[x][y-1] = true; //3 od dołu
          bricks[x][y-2] = true; //4 od dołu
        break;
        case 1: // o jeden w prawo
          bricks[x-1][y] = true; //1 od lewej
          bricks[x][y] = true; //2 od lewej
          bricks[x+1][y] = true; //3 od lewej
          bricks[x+2][y] = true; //4 od lewej
        break;
        case 2: // o dwa
          bricks[x][y+2] = true; //1 od dołu
          bricks[x][y+1] = true; //2 od dołu
          bricks[x][y] = true; //3 od dołu
          bricks[x][y-1] = true; //4 od dołu
        break;
        case 3: // o jeden w lewo
          bricks[x-2][y] = true; //1 od lewej
          bricks[x-1][y] = true; //2 od lewej
          bricks[x][y] = true; //3 od lewej
          bricks[x+1][y] = true; //4 od lewej
        break;
      }
    break;
  }
}

//--------------Drawing little block (next block indicator)-------------------
void DrawMiniShape(char shape)
{
  switch(shape)
  {
    case 'O':
      u8g2.drawStr(36,122,"NEXT:");
      u8g2.drawFrame(56,119,3,3);
      u8g2.drawFrame(56,117,3,3);
      u8g2.drawFrame(58,117,3,3);
      u8g2.drawFrame(58,119,3,3);
    break;
    case 'Z':
      u8g2.drawStr(36,122,"NEXT:");
      u8g2.drawFrame(60,119,3,3);
      u8g2.drawFrame(58,119,3,3);
      u8g2.drawFrame(58,117,3,3);
      u8g2.drawFrame(56,117,3,3);
    break;
    case 'S':
      u8g2.drawStr(36,122,"NEXT:");
      u8g2.drawFrame(56,119,3,3);
      u8g2.drawFrame(58,119,3,3);
      u8g2.drawFrame(58,117,3,3);
      u8g2.drawFrame(60,117,3,3);
    break;
    case 'L':
      u8g2.drawStr(36,122,"NEXT:");
      u8g2.drawFrame(56,115,3,3);
      u8g2.drawFrame(56,117,3,3);
      u8g2.drawFrame(56,119,3,3);
      u8g2.drawFrame(58,119,3,3);
    break;
    case 'J':
      u8g2.drawStr(36,122,"NEXT:");
      u8g2.drawFrame(58,115,3,3);
      u8g2.drawFrame(58,117,3,3);
      u8g2.drawFrame(56,119,3,3);
      u8g2.drawFrame(58,119,3,3);
    break;
    case 'T':
      u8g2.drawStr(36,122,"NEXT:");
      u8g2.drawFrame(60,117,3,3);
      u8g2.drawFrame(58,117,3,3);
      u8g2.drawFrame(56,117,3,3);
      u8g2.drawFrame(58,119,3,3);
    break;
    case 'I':
      u8g2.drawStr(36,122,"NEXT:");
      u8g2.drawFrame(58,113,3,3);
      u8g2.drawFrame(58,115,3,3);
      u8g2.drawFrame(58,117,3,3);
      u8g2.drawFrame(58,119,3,3);
    break;
  }
}

//----------------Cheacking if any row is full-----------------------
void checkRows()
{
  for(byte i = 0; i < 10; i++) //sprawdzenie, czy klocki sięgnęły sufitu
  {
    if(bricks[i][0])
    {
      gameOver();
      break;
    }
  }

  //----------checking for full lines (rows)-------------
  byte r = 0;
  for(byte j=19; j>0; j--)
  {
    byte n = 0;
    for(byte i=0; i<10; i++)
    {
      if(bricks[i][j])
        n++;
    }
    if(n == 10) //if entire line (row) is full
    {
      for(byte i=0; i<10; i++) //remove that line
      {
        bricks[i][j] = false;
      }
      for(byte k=j; k>0; k--) //Move all the lines above one unit down
      {
        for(byte i=0; i<10; i++)
        {
          if(bricks[i][k-1])
            bricks[i][k] = true;
          else
            bricks[i][k] = false;
        }
      }
      r++;
      lines++;
      switch(r) //Points for clearing a row are dependent on number of rows cleared at one time
      {
        case 1:
          score += 40 * lvl;
        break;
        case 2:
          score += 100 * lvl;
        break;
        case 3:
          score += 300 * lvl;
        break;
        case 4: //TETRIZ!
          score += 1200 * lvl;
          r = 0;
        break;
      }
      j++;
    }
  }
  for(byte i=0; i<10; i++) //Creating "floor" for blocks to stop at the bottom of the matrix
  {
    bricks[i][20] = true;
  }
  
  if(lines >= 10) //leveling
  {
    lvl = 2;
    if(lines >= 20)
    {
      lvl = 3;
      if(lines >= 30)
      {
        lvl = 4;
        if(lines >= 40)
        {
          lvl = 5;
          if(lines >= 50)
          {
            lvl = 6;
            if(lines >= 60)
            {
              lvl = 7;
              if(lines >= 70)
              {
                lvl = 8;
                if(lines >= 80)
                {
                  lvl = 9;
                  if(lines >= 90)
                  {
                    lvl = 10;
                  }
                }
              }
            }
          }
        }
      }
    }
  }
}
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
    u8g2.drawButtonUTF8(32, 32, U8G2_BTN_HCENTER|U8G2_BTN_BW1, 34,  2,  3, "loading...");
    
    u8g2.sendBuffer();
    Serial.println("uploading...");
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
void setup(void)
{
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
   kb.init();
  //------------Buttons---------------


  //Initialization of screen
  u8g2.begin();
  u8g2.setDisplayRotation(U8G2_R1);
  
  //-------------Start screen-------------------
    u8g2.setFont(u8g2_font_pieceofcake_mel_tr);
    u8g2.drawStr(5,50,"TETRIZ");
    u8g2.setFont(u8g2_font_micro_tr);
    u8g2.drawStr(2,58,"Arduino edition");
    u8g2.drawStr(28,70,"by");
    u8g2.drawStr(22,77,"Jakub");
    u8g2.drawStr(9,84,"Niewiarowski");
    u8g2.drawStr(24,94,"2022");
    u8g2.sendBuffer();
    delay(3000);

  //-----------Initializing block--------------
  randomSeed(analogRead(0));
  shape = random(0,7);
  nextShape = random(0,7);
  shape = random(0,7);
}

void loop(void) {
  kb.update();
    if (kb.getRisingEdgeKey() == std::make_pair(0, 0)) {
        Serial.println("uploading new software");
        updateFromFS(SD, "/main.bin");
        rebootEspWithReason("main uploaded!!");
    }
  //-----------------------------Input and displaying (20 times per second)------------------
  if(cycle % 5 == 0) //1 cycle = 10ms
  {
    if(kb.getKey(2, 2).getIsPressed() && !input && x < 9) //right
    {
      if(checkShape(x,y,1))
      {
        clearShape(x,y);
        x++;
        drawShape(x,y);
        input = true;
      }
    }
    else if(kb.getKey(0, 2).getIsPressed() && !input && x > 0) //left
    {
      if(checkShape(x,y,2))
      {
        clearShape(x,y);
        x--;
        drawShape(x,y);
        input = true;
      }
    }
    else if(kb.getKey(0, 1).getIsPressed() && !input) //R (rotate right)
    {
      if(kb.getKey(2, 1).getIsPressed())
        pausegame();
        
      if(rotation == 0 || rotation == 2)
      {
        if(checkShape(x,y,3))
        {
          clearShape(x,y);
          rotation++;
          drawShape(x,y);
          input = true;
        }
      }
      else
      {
        if(checkShape(x,y,3))
        {
          if(rotation == 3)
          {
            clearShape(x,y);
            rotation = 0;
            drawShape(x,y);
            input = true;
          }
          else
          {
            clearShape(x,y);
            rotation++;
            drawShape(x,y);
            input = true;
          }
        }
      }
    }
    else if(kb.getKey(2, 1).getIsPressed() && !input) //L (rotate left)
    {
      if(kb.getKey(0, 1).getIsPressed())
        pausegame();
        
      if(rotation == 0 || rotation == 2)
      {
        if(checkShape(x,y,4))
        {
          if(rotation == 0)
          {
            clearShape(x,y);
            rotation = 3;
            drawShape(x,y);
            input = true;
          }
          else
          {
            clearShape(x,y);
            rotation--;
            drawShape(x,y);
            input = true;
          }
        }
      }
      else
      {
        if(checkShape(x,y,4))
        {
          clearShape(x,y);
          rotation--;
          drawShape(x,y);
          input = true;
        }
      }
  }
  else if(kb.getKey(3, 2).getIsPressed() && !input) // H (hard drop)
  {  
    for(byte i = y; i < 20; i++)
    {
      if(!checkShape(x,i,0))
      {
        score += (i - y)*2;
        clearShape(x,y);
        y = i;
        drawShape(x,y);
        input = true;
        break;
      }
    }
  }
  else
  {
    input = false;
  }
  
  if(kb.getKey(4, 2).getIsPressed()) //S (soft drop)
  {
    s = 5*(lvl+2);
  }
  else
  {
    s = 100;
  }
  
//--------------------Drawing of blocks and game statistics-----------------
    u8g2.clearBuffer();
    u8g2.drawFrame(6,0,52,102);
    u8g2.drawStr(1,112,"SCORE:"); u8g2.setCursor(26, 112); u8g2.print(score);
    u8g2.drawStr(1,122,"LEVEL:"); u8g2.setCursor(26, 122); u8g2.print(lvl);
    switch(nextShape) // Next shape (little shape in statistics)
    {
      case 0:
        DrawMiniShape('O');
      break;
      case 1:
        DrawMiniShape('Z');
      break;
      case 2:
        DrawMiniShape('S');
      break;
      case 3:
        DrawMiniShape('L');
      break;
      case 4:
        DrawMiniShape('J');
      break;
      case 5:
        DrawMiniShape('T');
      break;
      case 6:
        DrawMiniShape('I');
      break;
    }
    //----------Drawing bricks on matrix-------------
    for(byte j=0; j<20; j++)
    {
      for(byte i=0; i<10; i++)
      {
        if(bricks[i][j])
        {
          u8g2.drawFrame((i*5)+7,(j*5)+1,5,5);
          u8g2.drawPixel((i*5)+9,(j*5)+3);
        }
      }
    }
    u8g2.sendBuffer();
}
 delay(10);
  
//----------------falling (speed is influenced by lvl)--------------------------
  if(cycle >= (s / (lvl + 2)))
  {
    clearShape(x,y);
    if(checkShape(x,y,0)) //falling (checking if block can fall [move down by 1 unit])
    {
      y++;
    }
    else //block has fallen
    {
      drawShape(x,y);
      y = 1;
      x = 5;
      checkRows();
      rotation = 0;
      shape = nextShape;
      //---------------Getting next shape--------------
      if(lastI < 7) //Preventing from a "starving" of I block (lack of I block too many times in a row)
      {
        if(prevSCounter >= 1) //Preventing from drawing the same shape too many times in a row
        {
          do
            nextShape = random(0,7);
          while(nextShape == shape);
        }
        else
        {
          nextShape = random(0,7);
        }
        if(nextShape == shape)
          prevSCounter++;
        else
          prevSCounter = 0;
        if(nextShape == 6)
          lastI = 0;
        else
          lastI++;
      }
      else //If last I block was was 7 blocks ago then next shape must be I
      {
        nextShape = 6;
        lastI = 0;
      }
    }
    drawShape(x,y);

    for(byte i=0; i<10; i++) //Creating "floor" for blocks to stop at the bottom of the matrix
    {
      bricks[i][20] = true;
    }
    
    cycle = 0;
  }
  
  cycle++;
}