#include "Slicer.h"
#include "Constants.h"
#include "OptimizedModel.h"
#include "Segment.h"

#include <cstdlib>
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
  std::cout << "Inited slicer, layers size=" << layers.size() << std::endl;
}

//切割，将切割出的切线段分进每个layer中
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
        int p1_idx = model->facets[j].index[0];
        int p2_idx = model->facets[j].index[1];
        int p3_idx = model->facets[j].index[2];
        Point a = model->points[p1_idx];
        Point b = model->points[p2_idx];
        Point c = model->points[p3_idx];
        float z1 = model->points[p1_idx].z;
        float z2 = model->points[p2_idx].z;
        float z3 = model->points[p3_idx].z;
        float z = layers[i].z;
        //根据不同的三角形方向，选择正确的调用顺序，以使得切线段的起点和重点正确
        if (z1 > z && z2 <= z && z3 <= z) {
          seg = cutSegment(a, b, c, z);
          //std::cout << "case 1" << std::endl;
        } else if (z3 > z && z1 <= z && z2 <= z) {
          seg = cutSegment(c, a, b, z);
            //std::cout << "case 2" << std::endl;
        } else if (z2 > z && z3 <= z && z1 <= z) {
          seg = cutSegment(b, c, a, z);
            //std::cout << "case 3" << std::endl;
        } else if (z1 < z && z2 >= z && z3 >= z) {
          seg = cutSegment(a, c, b, z);
            //std::cout << "case 4" << std::endl;
        } else if (z3 < z && z1 >= z && z2 >= z) {
          seg = cutSegment(c, b, a ,z);
            //std::cout << "case 5" << std::endl;
        } else if (z2 < z && z3 >= z && z1 >= z) {
          seg = cutSegment(b, a, c, z);
            //std::cout << "case 6" << std::endl;
        } else {
          // should not reach here
          std::cout << "Error when cutting segment" << std::endl <<
          "z1 = " << z1 << std::endl <<
          "z2 = " << z2 << std::endl <<
          "z3 = " << z3 << std::endl <<
          "z = " << z << std::endl <<
          "i=" << i << std::endl <<
          "j=" << j << std::endl;
          exit(-1);
        }
        seg.facetIndex = j;
        facet2segMap[j].emplace_back(i, layers[i].segments.size()); // 记录一个facet中包含的segment索引
        bool dup = false;
        for (auto old_seg: layers[i].segments) {
            //已存在这个线段
            if (old_seg.start == seg.start && old_seg.end == seg.end) {
                dup = true;
                break;
            }
        }
        if (!dup) layers[i].segments.emplace_back(seg);
      }
    }
  }
  std::cout << "finish adding segemnts to layers" << std::endl;
  // debuging
  // for (auto each: layers) {
  //   std::cout << each.segments.size() << std::endl;
  // }
}

//计算切线段的坐标信息
Segment Slicer::cutSegment(Point& p1, Point& p2, Point& p3, float z) {
  Segment ret;
  ret.start = p1 + (p2 - p1) * ((z - p1.z) / (p2.z - p1.z));
  ret.start.z = z;
  ret.end = p1 + (p3 - p1) * ((z - p1.z) / (p3.z - p1.z));
  ret.end.z = z;
  return ret;
}

//为每一层layer处理出相应的polygons
void Slicer::genPolygons() {
  for (int layer_id = 0; layer_id < layers.size(); ++layer_id) {
    // 对于每一个layer
    int seg_left = layers[layer_id].segments.size();
    int seg_size = seg_left;
    std::cout << "layer_id=" << layer_id << std::endl;
    while (seg_left > 0) {
      std::cout << "seg_left=" << seg_left << std::endl;
      for (int i = 0; i < seg_size; ++i) {
        Segment seg1 = layers[layer_id].segments[i];
        Segment last = seg1;
        if (!seg1.addedToPoly) {
          // 找到一个新的线段
          Polygon poly;
          seg1.addedToPoly = true;
          poly.segments.emplace_back(seg1);
          --seg_left;
          while (true) {
            //std::cout << "seg_left=" << seg_left << std::endl;
            for (int j = 0; j < seg_size; ++j) {
              if (i == j) continue; //跟起点同一个，跳过
              Segment seg2 = layers[layer_id].segments[j];
              if (seg2.addedToPoly) continue; //已被添加，跳过
              std::cout << "i=" << i << " j=" << j << std::endl;
              std::cout << "last.start: " << last.start << std::endl;
              std::cout << "last.end: " << last.end << std::endl;
              std::cout << "seg2.start: " << seg2.start << std::endl;
              std::cout << "seg2.end: " << seg2.end << std::endl;
              if (seg2.start == last.end) {
                // 首尾相接
                poly.segments.emplace_back(seg2);
                seg2.addedToPoly = true;
                --seg_left;
                last = seg2;
                break;
              }
            }
            if (last.end == seg1.start) {
              // 找完一个封闭多边形
              layers[layer_id].polygons.emplace_back(poly);
              break;
            }
          }
        } // if 该线段未被添加
      }
    }
  }
  std::cout << "finish gen polygons" << std::endl;
}