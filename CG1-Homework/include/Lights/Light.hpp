#ifndef Light_HPP
#define Light_HPP

#include "../Algebra/Point.hpp"
#include "../Algebra/Vec3.hpp"
#include "../Algebra/Ray.hpp"
#include "../Objects/Object.hpp"
#include "../Algebra/Intensity.hpp"

class Light
{
public:
    
    virtual Intensity lighting(const Object& inter_obj, std::vector<Object*> objs, const Vec3& intersection, const Ray& Eye) const = 0;
    
};
#endif