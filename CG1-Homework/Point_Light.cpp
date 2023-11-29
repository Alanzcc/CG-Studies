#ifndef Point_Light_HPP
#define Point_Light_HPP

#include "Light.hpp"

class Point_Light : public Light
{
public:
    Point origin;
    Vector direction;
    Intensity light_color;
    Point decay;


    Point_Light(Point origin, Vector direction, Intensity light_color, Point decay);
    Intensity lighting(const Object& inter_obj, std::vector<Object*> objs, const Vector& intersection, const Ray& Eye) const override;

};

#endif
