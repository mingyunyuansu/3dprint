#include <iostream>

#include "InputFromSTL.h"
#include "OptimizedModel.h"
#include "STL2VTK.h"
#include "Slicer.h"
#include "Layers2VTK.h"
#include "Filler.h"
#include "Filler2VTK.h"

int main() {
    InputFromSTL inp;
    OptimizedModel model;
    inp.init(model);
    std::cout << "Points number: " << model.points.size() << std::endl;
    std::cout << "Facets number: " << model.facets.size() << std::endl;

    //生成未切片前的vtk
    STL2VTK vtk;
    vtk.generate(model);

    Slicer slicer;
    slicer.init(&model);
    slicer.Slicing();
    slicer.genPolygons();

    Layers2VTK layer_vtk;
    layer_vtk.init(&slicer);
    layer_vtk.generate();

    Filler filler;
    filler.init(&slicer);
    filler.Fill();

    Filler2VTK filler_vtk(&filler);
    filler_vtk.generate();

}
