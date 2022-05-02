
#ifndef NEO_STL2VTK_H
#define NEO_STL2VTK_H

#include "OptimizedModel.h"

class STL2VTK {
public:
    STL2VTK() = default;
    void generate(const OptimizedModel& model, std::string path = "output.vtk");
};


#endif //NEO_STL2VTK_H
