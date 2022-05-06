//
//

#ifndef NEO_FILLER_H
#define NEO_FILLER_H


#include "Slicer.h"

using PolyId = std::pair<int, int>;

class Filler {
public:
  Filler() = default;
  void init(Slicer* slicer_);
  void Fill();
  Slicer* slicer{nullptr};
  std::map<PolyId, std::vector<Polygon>> polyMap; //此map存储所有层中，每个polygon及其内部不断缩小的轮廓，<layerId, polyId>==>Polygon
};


#endif //NEO_FILLER_H
