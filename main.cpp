#include <iostream>

#include "InputFromSTL.h"
#include "OptimizedModel.h"
#include "STL2VTK.h"

int main() {
    InputFromSTL inp;
    OptimizedModel model;
    inp.init(model);
    std::cout << "Points number: " << model.points.size() << std::endl;
    std::cout << "Facets number: " << model.facets.size() << std::endl;

    STL2VTK vtk;
    vtk.generate(model);
}