#pragma once
#include "OptimizedModel.h"
#include "Segment.h"

class Polygon {
  public:
  std::vector<Point> points;
  std::vector<Segment> segments;
};