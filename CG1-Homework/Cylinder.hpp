// cylinder.hpp. The cylinder class definition - A class for creating cylinder primitive shapes. 
#ifndef CYLINDER_HPP
#define CYLINDER_HPP

#include <cmath>
#include <vector>
#include <optional>
#include <algorithm>
#include "vec3Math.hpp"
#include "Ray.hpp"

class Cylinder
{
    public:
        double radius;
        double height;
        std::vector<double> ambientReflex;
        std::vector<double> diffuseReflex;
        std::vector<double> specularReflex;
        int specularExponent;
        std::vector<double> centerTop;
        std::vector<double> centerBottom;
        

        Cylinder(double radius, double height, std::vector<double> ambientReflex, std::vector<double> diffuseReflex, std::vector<double> specularReflex, int specularExponent, std::vector<double> centerTop, std::vector<double> centerBottom);

        std::optional<std::vector<double>> doesItIntercept(Ray Ray);
        std::vector<double> Illumination(Ray Ray, std::vector<double> intensity);

    private:
    //u é o vetor é o vetor unitário que define a direção e o sentido do eixo do cilindro. Ele pode ser calculado a partir de centerTop e centerBottom
        std::vector<double> calculateU() const;

};

#endif