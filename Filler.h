//
//

#ifndef NEO_FILLER_H
#define NEO_FILLER_H


#include "Slicer.h"

#include <cmath>

using PolyId = std::pair<int, int>;

//直线的方程
struct Line {
    float k;
    float b;
};

static const int64_t clipper_ratio = 10000;

class Filler {
public:
  Filler() = default;
  void init(Slicer* slicer_);
  void Fill();
  void fillOnePolygon(PolyId polyId);
  Polygon offset(Polygon& poly);
  Point intersection(Segment& seg1, Segment& seg2);
  Line segmentFunction(Segment& seg);
  friend float diameter(Polygon& poly);
  friend float flatDisOfPoints(Point& a, Point& b);
  Slicer* slicer{nullptr};
  std::map<PolyId, std::vector<Polygon>> polyMap; //此map存储所有层中，每个polygon及其内部不断缩小的轮廓，<layerId, polyId>==>Polygons
};

#endif //NEO_FILLER_H
