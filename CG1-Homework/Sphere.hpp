#ifndef Sphere_HPP
#define Sphere_HPP

#include <cmath>
#include <vector>
#include <optional>
#include <algorithm>
#include "vec3Math.hpp"
#include "Ray.hpp"

class Sphere
{
    public:
        double radius;
        std::vector<double> center;
        std::vector<double> ambientReflex;
        std::vector<double> diffuseReflex;
        std::vector<double> specularReflex;
        int specularExponent;
        
        Sphere(double radius, std::vector<double> center, std::vector<double> ambientReflex,
        std::vector<double> diffuseReflex, std::vector<double> specularReflex,
        int specularExponent);

        std::optional<std::vector<double>> doesItIntercept(Ray Ray); 
        std::vector<double> Illumination(Ray Ray, std::vector<double> intensity);
};

#endif