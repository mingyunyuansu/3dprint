#include "OptimizedModel.h"
#include "Facet.h"

Pair Facet::getMinMaxZ() {
    float min = model->points[index[0]].z;
    float max = model->points[index[0]].z;
    for (int i = 1; i < 3; ++i) {
      if (min > model->points[index[i]].z) {
        min = model->points[index[i]].z;
      }
      if (max < model->points[index[i]].z) {
        max = model->points[index[i]].z;
      }
    }
    return std::make_pair(min, max);
}