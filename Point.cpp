#include "Point.h"
#include <sys/_pthread/_pthread_once_t.h>

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

Point& Point::operator*(float r) {
  this->x *= r;
  this->y *= r;
  return *this;
}

bool Point::operator==(Point &rhs) {
  return this->x == rhs.x && this->y == rhs.y && this->z == rhs.z;
}

std::ostream& operator<<(std::ostream& out, Point& p) {
  out << p.x << " " << p.y << " " << p.z << std::endl;
  return out;
}