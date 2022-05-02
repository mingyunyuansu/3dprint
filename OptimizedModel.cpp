
#include "OptimizedModel.h"

#include <cmath>

size_t OptimizedModel::hasher(Point &p) {
    std::hash<int> hash_func;
    // 由ratio控制精度
    return (hash_func(round(p.x * ratio))) ^
            (hash_func(round(p.y * ratio)) << 10) ^
            (hash_func(round(p.x * ratio)) << 20);
}