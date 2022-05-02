#include "Point.h"

Point& Point::operator+(Point& rhs) {
  this->x += rhs.x;
  this->y += rhs.y;
  return *this;
}

Point& Point::operator-(Point& rhs) {
  this->x -= rhs.x;
  this->y -= rhs.y;
  return *this;
}