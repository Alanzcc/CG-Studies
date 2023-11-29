#ifndef Light_HPP
#define Light_HPP

#include "Point.hpp"
#include "Vector.hpp"
#include "Ray.hpp"
#include "Object.hpp"
#include "Intensity.hpp"

class Light
{
public:
    
    virtual Intensity lighting(const Object& first, std::vector<Object*> objs, const Vector& intersection, const Ray& Eye) const = 0;
    
};
#endif