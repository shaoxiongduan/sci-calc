#include "fruit.h"
#include "Arduino.h"
#include "position.h"

Fruit::Fruit(Snake * snake) {
  this->randomize(snake);
  this->position.x = 10;
  this->position.y = 4;
}

void Fruit::randomize(Snake * snake) {
  uint8_t spaceCnt = 0;
  const uint8_t **body = snake->getBody();
  
  for(int i = 0; i < Snake::BODY_WIDTH; i++) {
    for(int j = 0; j < Snake::BODY_HEIGHT; j++) {
      if(body[i][j] == 0) {
        spaceCnt++;
      }
    }
  }

  uint8_t targetSpace = random(0, spaceCnt);
  spaceCnt = 0;
  for(int i = 0; i < Snake::BODY_WIDTH; i++) {
    for(int j = 0; j < Snake::BODY_HEIGHT; j++) {
      if(body[i][j] == 0) {
        if(targetSpace == spaceCnt) {
          this->position.x = i;
          this->position.y = j;
          return;
        }
        spaceCnt++;
      }
    }
  }
}

const Position Fruit::getPosition() {
  return this->position;
}
