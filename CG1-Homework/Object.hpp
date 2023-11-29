#ifndef Object_HPP
#define Object_HPP

#include <vector>
#include <cmath>
#include <optional>
#include <algorithm>

#include "Ray.hpp"
#include "Vector.hpp"
#include "Intensity.hpp"

class Object
{
	public:
       
        Intensity emissive_color;  
        Intensity ambient_color;
        Intensity diffuse_color;
        Intensity specular_color;
        double shininess;

        virtual std::optional<Vector> intercept(Ray &Ray) = 0;
       
        virtual std::optional<Vector> get_normal(const Vector &intersection) const = 0;

        virtual Intensity get_emissive_color() const = 0;
        virtual Intensity get_ambient_color() const = 0;
        virtual Intensity get_diffuse_color() const = 0;
        virtual Intensity get_specular_color() const = 0;
        virtual double get_shininess() const = 0;
};

#endif