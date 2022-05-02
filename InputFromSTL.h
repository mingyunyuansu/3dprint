
#ifndef NEO_INPUTFROMSTL_H
#define NEO_INPUTFROMSTL_H

#include "Constants.h"
#include "OptimizedModel.h"
#include "Point.h"
#include "Facet.h"

#include <vector>
#include <string>

class InputFromSTL {
public:
    const std::string SOLID = "solid";
    const std::string ENDSOLID = "endsolid";

    InputFromSTL() {
        this->path = stl_path;
    }
    void init(OptimizedModel& model);
    void processAdjFacets(OptimizedModel& model, int facetId);
    int isDupPoint(OptimizedModel& model, Point& point, int idx);
    int distance(OptimizedModel& model, Point& p1, Point& p2);
    bool found2PointsInFacets(OptimizedModel& model, int facetId, int p1, int p2);
    std::string path;
    std::vector<Point> points;

};


#endif //NEO_INPUTFROMSTL_H
