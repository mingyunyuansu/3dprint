

#include <string>
#include <iostream>
#include <fstream>
#include "STL2VTK.h"

using std::endl;

void STL2VTK::generate(const OptimizedModel &model, std::string path) {
    std::ofstream ofs(path);
    ofs << "# vtk DataFile Version 2.0" << endl;
    ofs << "STL Model Output" << endl;
    ofs << "ASCII" << endl;
    ofs << "DATASET UNSTRUCTURED_GRID" << endl;
    int pointCount = model.points.size();
    int facetCount = model.facets.size();

    ofs << "POINTS " << pointCount << " float" << endl;
    for (int i = 0; i < pointCount; ++i) {
        ofs << model.points[i].x << " " << model.points[i].y << " " << model.points[i].z << endl;
    }
    ofs << endl << "CELLS " << facetCount << " " << 4 * facetCount << endl;
    for (int i = 0; i < facetCount; ++i) {
        ofs << "3 " << model.facets[i].index[0] << " " << model.facets[i].index[1] << " " << model.facets[i].index[2] << endl;
    }
    ofs << endl << "CELL_TYPES " << facetCount << endl;
    for (auto& i: model.facets) {
        ofs << "5" << endl;
    }
}
