#include "Slicer.h"
#include "Constants.h"
#include "OptimizedModel.h"

#include <iostream>

void Slicer::init(OptimizedModel* model) {
  this->model = model;
  //切片层做准备，需要找到所有切片的最低高度和最高高度（可能有负数）
  Pair pair = model->facets[0].getMinMaxZ();
  float min = pair.first;
  float max = pair.second;
  for (int i = 1; i < model->facets.size(); ++i) {
    pair = model->facets[i].getMinMaxZ();
    min = pair.first < min ? pair.first : min;
    max = pair.second > max ? pair.second : max;
  }

  int min_id = min / thickness - 1;
  int max_id = max / thickness + 1;
  for (int i = min_id; i <= max_id; ++i) {
    //当前高度
    float curr = thickness * i;
    layers.emplace_back(curr);
  }
  std::cout << "Inited slicer, size=" << layers.size() << std::endl;
}