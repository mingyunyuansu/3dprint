#pragma once
// 整个切片模型
#include <vector>

#include "Constants.h"
#include "Facet.h"
#include "OptimizedModel.h"
#include "Layer.h"

class Slicer {
  public:
  std::vector<Layer> layers;
  OptimizedModel* model{nullptr};
  Slicer() = default;
  void init(OptimizedModel* model);
};