#ifndef Sphere_HPP
#define Sphere_HPP

#include "Object.hpp"

class Sphere: public Object
{ 
    public:
        double radius;
        Point center;
        Intensity emissive_color;
        Intensity ambient_color;
        Intensity diffuse_color;
        Intensity specular_color;
        double shininess;

        Sphere(double radius, Point center);
        Sphere(double radius, Point center, Intensity emissive_color, Intensity ambient_color,
                Intensity diffuse_color, Intensity specular_color, double shininess);
        
        std::optional<IntCol> intercept(const Ray &Ray) const override;
        std::optional<Vec3> get_normal(const Vec3 &intersection) const override;
        Intensity get_emissive_color() const override;
        Intensity get_ambient_color() const override;
        Intensity get_diffuse_color() const override;
        Intensity get_specular_color() const override;
        double get_shininess() const override;
};

#endif