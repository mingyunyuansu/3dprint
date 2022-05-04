#ifndef NEO_LAYERS2VTK_H
#define NEO_LAYERS2VTK_H


#include "Slicer.h"

class Layers2VTK {
public:
    Slicer* slicer{nullptr};
    Layers2VTK() = default;
    void init(Slicer* slicer) {
      this->slicer = slicer;
    }
    void generate(const std::string& path="./layers.vtk");
};


#endif //NEO_LAYERS2VTK_H
