//
// Created by ByteDance on 2022/5/7.
//

#include "Filler2VTK.h"

#include <fstream>

using std::endl;

Filler2VTK::Filler2VTK(Filler* filler) {
  this->filler = filler;
}

void Filler2VTK::generate(std::string path) {
  std::ofstream ofs(path);
  ofs << "# vtk DataFile Version 2.0" << endl;
  ofs << "STL Model Output" << endl;
  ofs << "ASCII" << endl;
  ofs << "DATASET UNSTRUCTURED_GRID" << endl;
  int cntPoint = 0, cntFacet = 0;
  for (auto each: filler->polyMap) {
    for (int i = 0; i < each.second.size(); ++i) {
      cntPoint += each.second[i].points.size();
    }
    cntFacet += each.second.size();
  }

  ofs << "POINTS " << cntPoint << " float" << endl;
  for (auto each: filler->polyMap) {
    for (Polygon poly : each.second) {
      for (Point p : poly.points) {
        ofs << p.x << " " <<
        p.y << " " <<
        p.z << endl;
      }
    }
  }

  ofs << endl << "CELLS " << cntFacet << " " << 2 * cntFacet + cntPoint << endl;
  int cnt = 0;
  int tmp = 0;
  for (auto each_value : filler->polyMap) {
    for (auto each_poly : each_value.second) {
      tmp = cnt;
      ofs << each_poly.points.size() + 1 << " ";
      for (auto each_p: each_poly.points) {
        ofs << cnt << " ";
        ++cnt;
      }
      ofs << tmp << endl;
    }
  }

  ofs << endl << "CELL_TYPES " << cntFacet << endl;
  for (int i = 0; i < cntFacet; ++i) {
    ofs << "4" << endl;
  }
  ofs.close();
  std::cout << "filler 2 vtk finished" << endl;
}