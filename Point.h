
#ifndef NEO_POINT_H
#define NEO_POINT_H

#include <iostream>

class Point {
public:
    float x, y ,z;
    Point() = default;
    Point(float _x, float _y, float _z): x(_x), y(_y), z(_z) {}
    Point& operator+(Point& rhs);
    Point& operator-(Point& rhs);
    Point& operator*(float r);
    bool operator==(Point& rhs);
    float disTo(Point& p);
    friend std::ostream& operator<<(std::ostream& out, Point& p);
};


#endif //NEO_POINT_H
