#pragma once
// 整个切片模型
#include <map>
#include <utility>
#include <vector>

#include "Constants.h"
#include "Facet.h"
#include "OptimizedModel.h"
#include "Layer.h"

using SPair = std::pair<size_t, size_t>;

class Slicer {
  public:
    const float dis1 = 0.02; // 小于dis1的视为一个点
    const float dis2 = 10.0; // 介于dis1 dis2的补一条线，否则fail
  std::vector<Layer> layers;
  std::map<size_t, std::vector<SPair>> facet2segMap; // 根据一个facet id，查找该facet中都有哪些segment，segment的格式是pair<layer_id, segment_id> 
  OptimizedModel* model{nullptr};
  Slicer() = default;
  void init(OptimizedModel* model);
  void Slicing();
  Segment cutSegment(Point& p1, Point& p2, Point& p3, float z);
  void genPolygons();
};