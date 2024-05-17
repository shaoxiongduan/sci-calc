#include "Arduino.h"
#include "snake.h"

Snake::Snake() {
  this->body = new uint8_t *[Snake::BODY_WIDTH];
  for(uint8_t i = 0; i < Snake::BODY_WIDTH; i++) {
    this->body[i] = new uint8_t[Snake::BODY_HEIGHT];
    for(uint8_t j = 0; j < Snake::BODY_HEIGHT; j++) {
      this->body[i][j] = 0;
    }
  }
  this->body[Snake::BODY_WIDTH / 4 - 1][Snake::BODY_HEIGHT / 2] = 1;
  this->body[Snake::BODY_WIDTH / 4][Snake::BODY_HEIGHT / 2] = 2;
  this->head.x = Snake::BODY_WIDTH / 4;
  this->head.y = Snake::BODY_HEIGHT / 2;
  this->direction = RIGHT;
  this->turnDirection = this->direction;
}

Snake::~Snake() {
  for(uint8_t i = 0; i < Snake::BODY_WIDTH; i++) {
    delete[] this->body[i];
  }
}

Position Snake::nextHeadPosition() {
  Position next(this->head);
  switch(this->turnDirection) {
    case UP:
      next.y -= 1;
      break;
    case LEFT:
      next.x -= 1;
      break;
    case DOWN:
      next.y += 1;
      break;
    case RIGHT:
      next.x += 1;
      break;
  }
  return next;
}

void Snake::turn(Direction direction) {
  if((direction + 2) % 4 != this->direction) {
    this->turnDirection = direction;  
  }
}

void Snake::advance() {
  Position nextHead = this->nextHeadPosition();
  this->direction = this->turnDirection;
  if(nextHead.x < 0 || nextHead.y < 0) this->alive = false;
  if(nextHead.x >= Snake::BODY_WIDTH || nextHead.y >= Snake::BODY_HEIGHT) this->alive = false;
  else if(this->body[nextHead.x][nextHead.y] > 1) this->alive = false;

  if(!this->alive) return;
  this->head = nextHead;
  for(int i = 0; i < Snake::BODY_WIDTH; i++) {
    for(int j = 0; j < Snake::BODY_HEIGHT; j++) {
      if(this->body[i][j] > 0) {
        this->body[i][j]--;
      }
    }
  }
  this->body[this->head.x][this->head.y] = this->bodyLength;
}

void Snake::grow() {
  this->bodyLength++;
  for(int i = 0; i < Snake::BODY_WIDTH; i++) {
    for(int j = 0; j < Snake::BODY_HEIGHT; j++) {
      if(this->body[i][j] > 0) {
        this->body[i][j]++;
      }
    }
  }
}

const bool Snake::isAlive() {
  return this->alive;
}

const uint8_t Snake::getPoints() {
  return this->bodyLength - 2;
}

const Position Snake::getHeadPosition() {
  return this->head;
}

const uint8_t ** Snake::getBody() {
  return (const uint8_t **)this->body;
}
