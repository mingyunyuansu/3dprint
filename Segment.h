#pragma once

#include "Point.h"

class Segment {
  public:
  // 切线段类
  Point start, end;
  int facetIndex;
  bool addedToPoly{false};
};