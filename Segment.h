#pragma once

#include "Point.h"

class Segment {
  public:
  // 切线段类
  Segment() = default;
  Segment(Point& a, Point& b): start(a), end(b) {}
  Point start, end;
  int facetIndex;
  bool addedToPoly{false};
};