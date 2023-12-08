#include "TriangularPlane.hpp"

TriangularPlane::TriangularPlane(Point P1, Point P2, Point P3, Intensity ambient_color, Intensity diffuse_color, Intensity specular_color, double shininess):
    Plane(center, normal, emissive_color, ambient_color, diffuse_color, specular_color, shininess), P1{P1}, P2{P2}, P3{P3} 
    {
        Vec3 r1 = P1 - P0;
        Vec3 r2 = P2 - P0;
        Vec3 normal = (r1.cross(r2)).normalize();
    }


std::optional<IntCol> TriangularPlane::intercept(Ray &Ray) const {
    double k = ((Ray.direction - P0) * normal) / (Ray.direction * normal);
    if (k < 0) {
        return {};
    }

    Point intersectionPoint = Ray.origin + k * Ray.direction;

    Vec3 r1 = P1 - P0;
    Vec3 r2 = P2 - P0;
    Vec3 v = intersectionPoint - P0;
    double denominator = r1.cross(r2) * normal;

    double c1 = (v.cross(r2) * normal) / denominator;
    double c2 = (r1.cross(v) * normal) / denominator;
    double c3 = 1 - c1 - c2;
    
    if (c1 < 0 || c2 < 0 || c3 < 0) {
        return {};
    }

    return std::make_pair(intersectionPoint, get_emissive_color()
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