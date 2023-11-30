#ifndef Spotlight_HPP
#define Spotlight_HPP

#include "Light.hpp"

class Spotlight : public Light
{
public:
    Point origin;
    Vec3 direction;
    Intensity light_color;
    Point decay;
    double theta;

    Spotlight(Point origin, Vec3 direction, Intensity light_color, Point decay, double theta);
    Intensity lighting(const Object& inter_obj, std::vector<Object*> objs, const Vec3& intersection, const Ray& Eye) const override;

};

#endif
