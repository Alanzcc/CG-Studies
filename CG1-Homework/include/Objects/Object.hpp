#ifndef Object_HPP
#define Object_HPP

#include <vector>
#include <cmath>
#include <optional>
#include <algorithm>

#include "../Algebra/Ray.hpp"
#include "../Algebra/Vec3.hpp"
#include "../Algebra/Intensity.hpp"

using IntCol = std::pair<std::optional<Vec3>, Intensity>;
class Object
{
	public:
       
        Intensity emissive_color;  
        Intensity ambient_color;
        Intensity diffuse_color;
        Intensity specular_color;
        double shininess;

        virtual std::optional<Vec3> intercept(Ray &Ray) = 0;
       
        virtual std::optional<Vec3> get_normal(const Vec3 &intersection) const = 0;

        virtual Intensity get_emissive_color() const = 0;
        virtual Intensity get_ambient_color() const = 0;
        virtual Intensity get_diffuse_color() const = 0;
        virtual Intensity get_specular_color() const = 0;
        virtual double get_shininess() const = 0;
};

#endif