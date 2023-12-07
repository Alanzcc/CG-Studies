
#include "../include/Objects/Plane.hpp"

Plane::Plane(std::Vec3)

Plane::Plane(Point center, Vec3 normal, Intensity emissive_color, Intensity ambient_color, Intensity diffuse_color, Intensity specular_color, double shininess):
center(center), normal(normal), emissive_color(emissive_color), ambient_color(ambient_color), diffuse_color(diffuse_color), specular_color(specular_color), shininess(shininess)
{}


std::optional<IntCol> Plane::intercept(Ray Ray)
{
    Vec3 w = (center - Ray.origin);
    double denominator = Ray.direction.dot(normal);
    if (denominator == 0)
    {
        return {};
    }
    double intersectionScalar = w.dot(normal)/ denominator;
    if (intersectionScalar <= 0)
    {
        return {};
    }
    Vec3 intersectionPoint = (Ray.origin + Ray.direction * intersectionScalar);

    return std::make_pair(intersectionPoint, get_emissive_color());
}

//getters
Intensity
Intensity Plane::get_emissive_color() const
{
    return emissive_color;
}

Intensity Plane::get_ambient_color() const
{
    return ambient_color;
}

Intensity Plane::get_diffuse_color() const
{
    return diffuse_color;
}

Intensity Plane::get_specular_color() const
{
    return specular_color;
}

double Plane::get_shininess() const
{
    return shininess;
}

std::optional<Vec3> Plane::get_normal(const Vec3 &intersection) const
{
    return normal;
}


//translate
//transform


