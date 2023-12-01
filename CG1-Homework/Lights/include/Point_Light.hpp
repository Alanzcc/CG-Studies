#ifndef Point_Light_HPP
#define Point_Light_HPP

#include "Light.hpp"

class Point_Light : public Light
{
public:
    Point origin;
    Vec3 direction;
    Intensity light_color;
    Point decay;


    Point_Light(Point origin, Vec3 direction, Intensity light_color, Point decay);
    Intensity lighting(const Object& inter_obj, std::vector<Object*> objs, const IntCol& intersection, const Ray& Eye) const override;

};

#endif
