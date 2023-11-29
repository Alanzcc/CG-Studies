#ifndef Directional_Light_HPP
#define Directional_Light_HPP

#include "./Light.hpp"
#include <algorithm>

class Directional_Light : public Light
{
public:
    Point origin;
    Vector direction;
    Intensity light_color;

    Directional_Light(Vector direction, Intensity light_color);
    Intensity lighting(const Object &first, std::vector<Object*> objs, const Vector& intersection, const Ray& Eye) const override;


};

#endif