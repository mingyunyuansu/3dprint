#pragma once
//一个切片层
#include <vector>

#include "Polygon.h"
#include "Segment.h"

class Layer {
  public:
  float z;
  std::vector<Segment> segments;
  std::vector<Polygon> polygons;
  Layer(float z): z(z) {
  }
};