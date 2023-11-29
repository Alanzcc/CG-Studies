#ifndef Spotlight_HPP
#define Spotlight_HPP

#include "Light.hpp"

class Spotlight : public Light
{
public:
    Point origin;
    Vector direction;
    Intensity light_color;
    Point decay;
    double theta;

    Spotlight(Point origin, Vector direction, Intensity light_color, Point decay, double theta);
    Intensity lighting(const Object& inter_obj, std::vector<Object*> objs, const Vector& intersection, const Ray& Eye) const override;

};

#endif
