
#ifndef NEO_FACET_H
#define NEO_FACET_H

#include <utility>

using Pair = std::pair<float, float>;

class OptimizedModel;

class Facet {
public:
    Facet() = default;
    Facet(int a, int b, int c) {
        index[0] = a;
        index[1] = b;
        index[2] = c;
    }
    void set_model(OptimizedModel* model) {
        this->model = model;
    }
    Pair getMinMaxZ();
    int index[3];
    OptimizedModel* model{nullptr};
};


#endif //NEO_FACET_H
