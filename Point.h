
#ifndef NEO_POINT_H
#define NEO_POINT_H


class Point {
public:
    float x, y ,z;
    Point() = default;
    Point(float _x, float _y, float _z): x(_x), y(_y), z(_z) {}
};


#endif //NEO_POINT_H
