
#include "../include/Objects/Plane.hpp"

Plane::Plane(std::Vec3)

Plane::Plane(Point center, Vec3 normal, Intensity emissive_color, Intensity ambient_color, Intensity diffuse_color, Intensity specular_color, double shininess):
center(center), normal(normal), emissive_color(emissive_color), ambient_color(ambient_color), diffuse_color(diffuse_color), specular_color(specular_color), shininess(shininess)
{}


std::optional<std::vector<double>> Plane::intercept(Ray Ray)
{
    Vec3 w = center - Ray.origin);;
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

