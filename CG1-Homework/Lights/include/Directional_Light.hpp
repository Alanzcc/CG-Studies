#ifndef Directional_Light_HPP
#define Directional_Light_HPP

#include "Light.hpp"
#include <algorithm>

class Directional_Light : public Light
{
public:
    Point origin;
    Vec3 direction;
    Intensity light_color;

    Directional_Light(Vec3 direction, Intensity light_color);
    Intensity lighting(const Object& inter_obj, std::vector<Object*> objs, const IntCol& intersection, const Ray& Eye) const override;


};

#endif