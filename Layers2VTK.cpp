#include "Layers2VTK.h"

#include <fstream>

using std::endl;

void Layers2VTK::generate(const std::string& path) {
  std::ofstream ofs(path);
  ofs << "# vtk DataFile Version 2.0" << endl;
  ofs << "STL Model Output" << endl;
  ofs << "ASCII" << endl;
  ofs << "DATASET UNSTRUCTURED_GRID" << endl;
  int cntPoint = 0, cntFacet = 0;
  for (int i = 0; i < slicer->layers.size(); ++i) {
    cntFacet += slicer->layers[i].polygons.size();
    for (int j = 0; j < slicer->layers[i].polygons.size(); ++j) {
      cntPoint += slicer->layers[i].polygons[j].points.size();
    }
  }

  ofs << "POINTS " << cntPoint << " float" << endl;
  for (int i = 0; i < slicer->layers.size(); ++i) {
    for (int j = 0; j < slicer->layers[i].polygons.size(); ++j) {
      for (int k = 0; k < slicer->layers[i].polygons[j].points.size(); ++k) {
        ofs << slicer->layers[i].polygons[j].points[k].x << " " <<
        slicer->layers[i].polygons[j].points[k].y << " " <<
        slicer->layers[i].z << endl;
      }
    }
  }

  ofs << endl << "CELLS " << cntFacet << " " << 2 * cntFacet + cntPoint << endl;
  int cnt = 0;
  int tmp = 0;
  for (int i = 0; i < slicer->layers.size(); ++i) {
    for (int j = 0; j < slicer->layers[i].polygons.size(); ++j) {
      tmp = cnt;
      ofs << slicer->layers[i].polygons[j].points.size() + 1 << " ";
      for (int k = 0; k < slicer->layers[i].polygons[j].points.size(); ++k) {
        ofs << cnt << " ";
        ++cnt;
      }
      ofs << tmp << endl;
    }
  }

  ofs << endl << "CELL_TYPES " << cntFacet << endl;
  for (int i = 0; i < cntFacet; i++) {
    ofs << "4" << endl;
  }
  ofs.close();
}
