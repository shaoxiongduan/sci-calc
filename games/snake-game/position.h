#include "Arduino.h"
#pragma once

class Position {
  public:
    Position(uint8_t x, uint8_t y);
    uint8_t x;
    uint8_t y;
    friend bool operator==(const Position &p1, const Position &p2);
    friend bool operator!=(const Position &p1, const Position &p2);
};
