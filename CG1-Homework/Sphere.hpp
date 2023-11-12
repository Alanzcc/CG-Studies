#ifndef Sphere_HPP
#define Sphere_HPP

#include "Object.hpp"

class Sphere : public Object 
{
    public:
        double radius;
        std::vector<double> center;

        Sphere(double radius, std::vector<double> center, std::vector<double> ambientReflex,
               std::vector<double> diffuseReflex, std::vector<double> specularReflex,
               int shininess);

        std::optional<std::vector<double>> doesItIntercept(Ray Ray);
        std::vector<double> Illumination(Ray Ray, std::vector<double> intensity);
};

#endif