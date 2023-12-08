#ifndef Light_HPP
#define Light_HPP

#include "Point.hpp"
#include "Vec3.hpp"
#include "Ray.hpp"
#include "Object.hpp"
#include "Intensity.hpp"

class Light
{
public:

    virtual Intensity lighting(const Object& inter_obj, std::vector<Object*> objs, const IntCol& intersection, const Ray& Eye) const = 0;

};
#endif
