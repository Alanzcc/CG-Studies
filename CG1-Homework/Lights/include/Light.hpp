#ifndef Light_HPP
#define Light_HPP

#include "../Algebra/include/Point.hpp"
#include "../Algebra/include/Vec3.hpp"
#include "../Algebra/include/Ray.hpp"
#include "../Objects/include/Object.hpp"
#include "../Lights/include/Intensity.hpp"

class Light
{
public:
    
    virtual Intensity lighting(const Object& inter_obj, std::vector<Object*> objs, const Vec3& intersection, const Ray& Eye) const = 0;
    
};
#endif