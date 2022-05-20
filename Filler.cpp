//
//

#include "Filler.h"
#include "polyclipping/clipper.hpp"

using ClipperLib::IntPoint;
//计算一个环的最大直径
float diameter(Polygon& poly) {
  Point p0 = poly.points[0];
  float ret = -1;
  for (int i = 1; i < poly.points.size(); ++i) {
    float dx = poly.points[i].x - p0.x;
    float dy = poly.points[i].y - p0.y;
    ret = ret < sqrt(dx * dx + dy * dy) ? sqrt(dx * dx + dy * dy) : ret;
  }
  std::cout << "diameter: " << ret << std::endl;
  return ret;
}

float flatDisOfPoints(Point& a, Point& b) {
  float dx = a.x - b.x;
  float dy = a.y - b.y;
  return sqrt(dx * dx + dy * dy);
}

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
  int cnt = 0;
  for (auto& each: polyMap) {
//    if (cnt != 50) {
//      ++cnt;
//      continue;
//    }
    if (each.second.empty()) {
      continue;
    }
    fillOnePolygon(each.first);
    ++cnt;
    //std::cout << cnt++ << std::endl;
  }
}

void Filler::fillOnePolygon(PolyId polyId) {
  int cnt = 0;
  while (true) {
    //if (cnt > 20) break;
    Polygon curr = polyMap[polyId].back();
    polyMap[polyId].emplace_back(offset(curr));
    //if (polyMap[polyId].back().points.size() == curr.points.size() ||
    if (curr.points.empty()) {
      break;
    }
    ++cnt;
  }
}

Polygon Filler::offset(Polygon &poly) {
  ClipperLib::Path path;
  for (auto p : poly.points) {
    path << IntPoint(p.x * clipper_ratio, p.y * clipper_ratio);
  }
  ClipperLib::ClipperOffset co;
  ClipperLib::Paths paths;
  co.AddPath(path, ClipperLib::jtMiter, ClipperLib::etClosedPolygon);
  co.Execute(paths, -h * clipper_ratio);
  Polygon ret;
  for (auto& each_path: paths) {
    for (auto& each_intp: each_path) {
      ret.points.emplace_back((double)each_intp.X / clipper_ratio, (double)each_intp.Y / clipper_ratio, poly.points[0].z);
    }
  }
  return ret;
}

//void Filler::fillOnePolygon(std::vector<Polygon> &vp) {
//  int cnt = 0;
//  while (true) {
//    if (cnt > 10) break; //太多了，说明这时缩segment反而在变大
//    Polygon lastone = vp.back();
//    Polygon newone;
//    if (diameter(lastone) < 3 * h) {
//      break;
//    }
//    //起始点预期重合，所以-1
//    for (int i = 0; i < lastone.segments.size() - 1; ++i) {
//      int seg_id1 = i - 1;
//      int seg_id2 = i;
//      int seg_id3 = i + 1;
//      if (seg_id1 < 0) {
//        seg_id1 = lastone.segments.size() - 1;
//      }
//      if (seg_id3 >= lastone.segments.size()) {
//        seg_id3 = 0;
//      }
//      Point start_ =
//              intersection(lastone.segments[seg_id1],
//                           lastone.segments[seg_id2]);
//      Point end_ =
//              intersection(lastone.segments[seg_id2],
//                           lastone.segments[seg_id3]);
//      if (newone.points.empty()) {
//        newone.points.push_back(start_);
//      }
//      if (flatDisOfPoints(start_, end_) >= h) {
//        //新的segment长度过小则直接视为一个点，不再添加
//        newone.points.push_back(end_);
//      }
//    }
//    //生成了一个新多边形的所有点
//    if (newone.points.size() < 3 || diameter(newone) < 3 * h) {
//      break;
//    }
//    //大小符合要求，开始串联所有点
//    for (int i = 0; i < newone.points.size(); ++i) {
//      int next = i + 1 >= newone.points.size() ? 0 : i + 1;
//      newone.segments.emplace_back(newone.points[i], newone.points[next]);
//    }
//    vp.emplace_back(newone);
//    cnt++;
//  }
//}
//
//Point Filler::intersection(Segment& seg1, Segment& seg2) {
//  Line l1 = segmentFunction(seg1);
//  Line l2 = segmentFunction(seg2);
//  //求交点
//  Point j;
//  j.x = (l2.b - l1.b) / (l1.k - l2.k);
//  j.y = (l1.k * l2.b - l2.k * l1.b) / (l1.k - l2.k);
//  j.z = seg1.start.z;
//  return j;
//}
//
//Line Filler::segmentFunction(Segment &seg) {
//  Point p1 = seg.start;
//  Point p2 = seg.end;
//  float k = (p2.y - p1.y) / (p2.x - p1.x);
//  float b = (p1.x * p2.y - p2.x * p1.y) / (p1.x - p2.x);
//  //float b = (p1.x * p1.y - p2.x * p2.y) / (p1.x - p2.x);
//  float m = h * sqrt((p2.x - p1.x) * (p2.x - p1.x) +
//          (p2.y - p1.y) * (p2.y - p1.y)) / (p2.x - p1.x);
//  return Line{k, b + m};
//}

