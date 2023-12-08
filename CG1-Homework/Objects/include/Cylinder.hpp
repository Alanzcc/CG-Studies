// cylinder.hpp. The cylinder class definition - A class for creating cylinder primitive shapes. 
/*
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
        std::vector<double> axis;
        int shininess;

        Cylinder(double radius, double height, std::vector<double> ambientReflex, std::vector<double> diffuseReflex, std::vector<double> specularReflex, int specularExponent, std::vector<double> centerTop, std::vector<double> centerBottom, int shininess);

        std::optional<std::vector<double>> doesItIntercept(Ray Ray);
        std::vector<double> Illumination(Ray Ray, std::vector<double> intensity);

    
};

#endif
*/

#ifndef CYLINDER_HPP
#define CYLINDER_HPP

#include <cmath>
#include <vector>
#include <optional>
#include <algorithm>

#include "../Algebra/include/Ray.hpp"
#include "../Algebra/include/Point.hpp"
#include "../Algebra/include/Vec3.hpp"
#include "../Lights/include/Light.hpp"
#include "../Lights/include/Intensity.hpp"
#include "Object.hpp"
#include "CircularPlane.hpp"

class Cylinder : public Object 
{
    public:
        double radius;
        double height;

        Point center_bottom;
        Vec3 axis;

        CircularPlane bottom;
        CircularPlane top;

        Intensity emissive_color;
        Intensity ambient_color;
        Intensity diffuse_color;
        Intensity specular_color;
        double shininess;
        
        // constructors
        Cylinder(double radius, double height, Point center_bottom, Vec3 axis, Intensity emissive_color,
         Intensity ambient_color, Intensity diffuse_color, Intensity specular_color, double shininess);
        Cylinder(double radius, double height, Point center_bottom, Vec3 axis);

        // check if ray intercepts the object
        std::optional<IntCol> intercept(const Ray &Ray) const override;
        
        // getters
        std::optional<Vec3> get_normal(const Vec3 &intersection) const override;
        Intensity get_emissive_color() const override;
        Intensity get_ambient_color() const override;
        Intensity get_diffuse_color() const override;
        Intensity get_specular_color() const override;
        double get_shininess() const override;


};

#endif