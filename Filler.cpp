//
//

#include "Filler.h"

//处理layers中所有现有多边形进数据结构中
void Filler::init(Slicer* slicer_) {
  this->slicer = slicer_;
  int64_t layer_cnt = 0, poly_cnt = 0;
  for (int l = 0; l < slicer->layers.size(); ++l) {
    ++layer_cnt;
    for (int p = 0; p < slicer->layers[l].polygons.size(); ++p) {
      polyMap[{l, p}].emplace_back(slicer->layers[l].polygons[p]);
      ++poly_cnt;
    }
  }
  std::cout << "Filler init over, layers: " << layer_cnt << ", polys: " << poly_cnt
  << ", map_size: " << polyMap.size() << std::endl;
}

//开始填充
void Filler::Fill() {
  for (int i = 0; i < slicer->layers.size(); ++i) {

  }
}