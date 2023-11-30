#ifndef Ray_HPP
#define Ray_HPP


#include "Point.hpp"
#include "Vec3.hpp"

class Ray
{
public:
    Point origin;
    Vec3 direction;

    Ray(Point origin, Vec3 direction);
    Ray(Point origin, Point direction);

    Point get_origin() const;
    Vec3 get_direction() const;
};

#endif