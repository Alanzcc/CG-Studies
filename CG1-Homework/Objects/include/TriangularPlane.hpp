#ifndef TRIANGULARPLANE_HPP
#define TRIANGULARPLANE_HPP

#include "Point.hpp"
#include "Vec3.hpp"
#include "Ray.hpp"
#include "Object.hpp" //erro
#include "Intensity.hpp"


class TriangularPlane : public Object {
    public:
        Point P1;
        Point P2;
        Point P3;
        Point center;
        Vec3 normal;
        Intensity ambient_color;
        Intensity diffuse_color;
        Intensity specular_color;
        double shininess;

        TriangularPlane(Point P1, Point P2, Point P3, Intensity ambient_color, Intensity diffuse_color, Intensity specular_color, double shininess);

        std::optional<IntCol> intercept(Ray &Ray) override;
        std::optional<Vec3> get_normal (const Point &intersection) override;
        Intensity get_emissive_color() override;
        Intensity get_ambient_color() override;
        Intensity get_diffuse_color() override;
        Intensity get_specular_color() override;
        double get_shininess() override;
};

    
#endif