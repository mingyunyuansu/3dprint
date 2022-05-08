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

class Filler {
public:
  Filler() = default;
  void init(Slicer* slicer_);
  void Fill();
  void fillOnePolygon(std::vector<Polygon>& vp);
  Point intersection(Segment& seg1, Segment& seg2);
  Line segmentFunction(Segment& seg);
  friend float diameter(Polygon& poly);
  friend float flatDisOfPoints(Point& a, Point& b);
  Slicer* slicer{nullptr};
  std::map<PolyId, std::vector<Polygon>> polyMap; //此map存储所有层中，每个polygon及其内部不断缩小的轮廓，<layerId, polyId>==>Polygons
};

#endif //NEO_FILLER_H
