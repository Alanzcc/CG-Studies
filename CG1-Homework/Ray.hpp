#ifndef Ray_HPP
#define Ray_HPP


#include "Point.hpp"
#include "Vector.hpp"

class Ray
{
public:
    Point origin;
    Vector direction;

    Ray(Point origin, Vector direction);
    Ray(Point origin, Point direction);

    Point get_origin() const;
    Vector get_direction() const;
};

#endif