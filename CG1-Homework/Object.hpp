#ifndef Object_HPP
#define Object_HPP

#include <vector>
#include <cmath>
#include <optional>
#include <algorithm>

#include "Ray.hpp"
#include "vec3Math.hpp"

class Object
{
	public:
        std::vector<double> ambientReflex;
        std::vector<double> diffuseReflex;
        std::vector<double> specularReflex;
        int shininess;

        virtual std::optional<std::vector<double>> doesItIntercept(Ray Ray) = 0;
        virtual std::vector<double> Illumination(Ray Ray, std::vector<double> intensity) = 0;
};

#endif