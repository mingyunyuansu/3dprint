//
// Created by ByteDance on 2022/5/7.
//

#ifndef NEO_FILLER2VTK_H
#define NEO_FILLER2VTK_H

#include "Filler.h"

class Filler2VTK {
public:
  Filler2VTK(Filler* filler);
  void generate(std::string path="filler.vtk");
  Filler* filler{nullptr};
};


#endif //NEO_FILLER2VTK_H
