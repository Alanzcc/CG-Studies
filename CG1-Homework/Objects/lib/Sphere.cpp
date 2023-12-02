#include "Sphere.hpp"


Sphere::Sphere(double radius, Point center, Intensity emissive_color, Intensity ambient_color, Intensity diffuse_color, Intensity specular_color, double shininess): Object(emissive_color, ambient_color, diffuse_color, specular_color, shininess)
{
    this->radius = radius;
    this->center = center;
}

std::optional<IntCol> Sphere::intercept(Ray &Ray)
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

    return std::make_pair(intersectionPoint, get_emissive_color());

}
// Fix issue with return type
/*std::optional<std::vector<double>> Sphere::doesItIntercept(Ray Ray)
{
    std::vector<double> w = minusVectors(Ray.initialPoint, center);
    double b = (2 * dotProduct(w, Ray.direction));
    double c = dotProduct(w, w) - (this->radius * this->radius);
    double delta = pow(b, 2) - (4 * c);
    if (delta < 0)
    {
        return {};
    }
    double x1 = (b - sqrt(delta)) / 2;
    double x2 = (b + sqrt(delta)) / 2;
    double intersectionScalar = std::min(((b - sqrt(delta)) / 2), ((b + sqrt(delta)) / 2));
    std::vector<double> intersectionPoint = plusVectors(Ray.initialPoint, multiplyByScalar(Ray.direction, intersectionScalar));
    return intersectionPoint;
}*/




