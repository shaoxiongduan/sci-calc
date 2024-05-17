#include "Arduino.h"
#include "position.h"

Position::Position(uint8_t x, uint8_t y) {
  this->x = x;
  this->y = y;
}

bool operator==(const Position &p1, const Position &p2) {
  return (p1.x == p2.x) && (p1.y == p2.y);
}

bool operator!=(const Position &p1, const Position &p2) {
  return !(p1 == p2);
}
