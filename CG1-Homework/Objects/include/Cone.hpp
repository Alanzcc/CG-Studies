#ifndef CONE_HPP
#define CONE_HPP

//all includes
#include "CircularPlane.hpp"
#include "Point.hpp"
#include "Vec3.hpp"
#include "Ray.hpp"
#include "Object.hpp"
#include "../Lights/include/Intensity.hpp"
#include <cmath>
#include <optional>
#include <utility>
#include <algorithm>
#include <optional>

class Cone : public Object
{
    public:
        double angle;
        double height;
        Point vertex;
        Vec3 axis;
        double radius;
        CircularPlane bottom;

        Intensity emissive_color;
        Intensity ambient_color;
        Intensity diffuse_color;
        Intensity specular_color;
        double shininess;

        Cone(double angle, double height, Point vertex, Vec3 axis, double radius, Intensity ambientReflex, Intensity diffuseReflex, Intensity specularReflex, int specularExponent, int shininess);

        std::optional<IntCol> intercept(Ray &Ray) override;
        std::optional<Vec3> get_normal(const Vec3 &intersection);
        Intensity get_emissive_color() const override;
        Intensity get_ambient_color() const override;
        Intensity get_diffuse_color() const override;
        Intensity get_specular_color() const override;
        double get_shininess() const override;
        
        
};

//cone will need cone's vertex, axis, angle, height and radius
//if you have centerBase, you can calculate V = C + Hn 
// intersectionPoint a tint^2 + 2b tint + c = 0
//v is V - Po
// a = (d . n)^2 - (d.d) cos^2(angle)
// b = (v.d)cos^2(angle) - (v.n)(d.n)
// c = (v . n)^2 - (v.v)cos^2(angle)

//delta < 0 -> no intersection 
//delta = 0 -> one intersection
//delta > 0 -> two intersection

//Pint = Po + tint d

//if a is zero, ray is parallel to 'geratriz' 

// it's inside the cone if 0<= (V-P) . n <= H


#endif