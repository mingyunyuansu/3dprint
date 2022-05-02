#include "Slicer.h"
#include "Constants.h"
#include "OptimizedModel.h"
#include "Segment.h"

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

void Slicer::Slicing() {
  for (int i = 0; i < layers.size(); ++i) {
    // 对于每一层
    for (int j = 0; j < model->facets.size(); ++j) {
      Pair pair = model->facets[j].getMinMaxZ();
      float curr_min = pair.first, curr_max = pair.second;
      if (layers[i].z > curr_min && layers[i].z < curr_max) {
        //该三角形在此切面中
        Segment seg;
        // 求交线的两点坐标
        seg.facetIndex = j;
        int p1_idx = model->facets[j].index[0];
        int p2_idx = model->facets[j].index[1];
        int p3_idx = model->facets[j].index[2];
        float z1 = model->points[p1_idx].z;
        float z2 = model->points[p2_idx].z;
        float z3 = model->points[p3_idx].z;
        //TODO: 完成根据不同的三角形方向，选择正确的调用顺序，以使得切线段的起点和重点正确
      }
    }
  }
}