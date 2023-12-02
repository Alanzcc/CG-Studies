#include "CircularPlane.hpp"
#include <iostream>

CircularPlane::CircularPlane(double radius):
    Plane(Point center, Vec3 normal, Intensity emissive_color, Intensity ambient_color, Intensity diffuse_color, Intensity specular_color, double shininess):
    radius(radius)
    {}


std::optional<IntCol> CircularPlane::intercept(Ray Ray)
{
    double denominator = Ray.direction.dot(normal);
    //std::cout << "Dem is: " << denominator << std::endl;

    //std::cout << "Num is: " << numerator << std::endl;

    if (denominator == 0)
    {
        return {};
    }
    double intersectionScalar = (center - Ray.origin).dot(normal)/ denominator;
    //std::cout << "Scalar is: " << intersectionScalar << std::endl;
    
    Vec3 intersectionPoint = Ray.origin + (Ray.direction * intersectionScalar);
   //std::cout << "Intersection point is: " << intersectionPoint << std::endl;

   double distance = (intersectionPoint - center).norm();
    //std::cout <<" Distance: " << distance << std::endl;

    if (distance > radius)
    {
        return {};
    }

    return std::make_pair(intersectionPoint, get_emissive_color());
    
}

//getters

Intensity CircularPlane::get_emissive_color()
{
    return emissive_color;
}

Intensity CircularPlane::get_ambient_color()
{
    return ambient_color;
}

Intensity CircularPlane::get_diffuse_color()
{
    return diffuse_color;
}

Intensity CircularPlane::get_specular_color()
{
    return specular_color;
}

double CircularPlane::get_shininess()
{
    return shininess;
}

std::optional<Vec3> CircularPlane::get_normal (const Vec3 &intersection)
{
    return normal;
}

//translate
//scale
//transform

