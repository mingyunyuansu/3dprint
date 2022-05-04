#pragma once
#include "OptimizedModel.h"
#include "Segment.h"

class Polygon {
  public:
  std::vector<int> points;
  std::vector<Segment> segments;
};