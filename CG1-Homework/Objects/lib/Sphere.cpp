#include "Sphere.hpp"


Sphere::Sphere(double r, Point c) : radius{ r }, center{ c }, emissive_color{ 1, 1, 1 },
ambient_color{ 1, 1, 1 }, diffuse_color{ 1, 1, 1 }, specular_color{ 1, 1, 1 }, shininess(1) {}

Sphere::Sphere(double r, Point c, Intensity e, Intensity a, Intensity d, Intensity sp,
    double sh) : radius{ r }, center{ c }, emissive_color{ e }, ambient_color{ a },
    diffuse_color{ d }, specular_color{ sp }, shininess{ sh } {}

std::optional<IntCol> Sphere::intercept(const Ray& Ray) const
{
    Vec3 w = Ray.origin - center;
    double b = 2 * w.dot(Ray.direction);
    double c = w.dot(w) - (radius * radius);
    double delta = pow(b, 2) - (4 * c);
    if (delta < 0)
    {
        return std::nullopt;
    }

    double x1 = (-b + sqrt(delta)) / 2;
    double x2 = (-b - sqrt(delta)) / 2;
    double intersectionScalar = std::min(x1, x2);
    Point intersectionPoint = Ray.origin + (Ray.direction * intersectionScalar);

    return std::make_pair(std::move(intersectionPoint), get_emissive_color());
}
std::optional<Vec3> Sphere::get_normal(const Point& intersection) const { return (intersection - center).normalize(); }
Intensity Sphere::get_emissive_color() const { return emissive_color; }
Intensity Sphere::get_ambient_color() const { return ambient_color; }
Intensity Sphere::get_diffuse_color() const { return diffuse_color; }
Intensity Sphere::get_specular_color() const { return specular_color; }
double Sphere::get_shininess() const { return shininess; }



