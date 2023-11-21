#include "CircularPlane.hpp"
#include <iostream>
CircularPlane::CircularPlane(double radius, std::vector<double> center, std::vector<double> normal, double constAttenuation, double linearAttenuation,
    double quadraticAttenuation, std::vector<double> ambientReflex,
    std::vector<double> diffuseReflex, std::vector<double> specularReflex, int shininess) : Plane(center, normal, constAttenuation,
    linearAttenuation, quadraticAttenuation, ambientReflex, diffuseReflex, specularReflex, shininess)
{
    this->radius = radius;
    
}

std::optional<std::vector<double>> CircularPlane::doesItIntercept(Ray Ray)
{
    double denominator = dotProduct(Ray.direction, this->normal);
    //std::cout << "Dem is: " << denominator << std::endl;

    //std::cout << "Num is: " << numerator << std::endl;

    if (denominator == 0)
    {
        return {};
    }
    double intersectionScalar = dotProduct(minusVectors(this->center, Ray.initialPoint), divideByScalar(this->normal, denominator));
    //std::cout << "Scalar is: " << intersectionScalar << std::endl;
    
    
    std::vector<double> intersectionPoint = plusVectors(Ray.initialPoint, multiplyByScalar(Ray.direction, intersectionScalar));
    double distance = norm(minusVectors(intersectionPoint, this->center));
    //std::cout <<" Distance: " << distance << std::endl;

    if (distance > this->radius)
    {
        return {};
    }
    return intersectionPoint;
}

std::vector<double> CircularPlane::Illumination(Ray Ray, std::vector<double> intensity)
{
    std::vector<double> illumination;
    std::vector<double> interPoint = doesItIntercept(Ray).value_or(std::vector<double>(3, -2));
    if (interPoint[0] != -2)
    {
        std::vector<double> light = normalize(minusVectors(Ray.initialPoint, interPoint));

        std::vector<double> reflected = minusVectors(multiplyByScalar(this->normal, 2 * dotProduct(light, this->normal)), light);

        std::vector<double> vision = multiplyByScalar(normalize(minusVectors(interPoint, Ray.initialPoint)), -1); // While cam = ray_source

        double diffusionFactor = dotProduct(light, this->normal);
        double specularFactor = pow(dotProduct(reflected, vision), this->shininess); 

        std::vector<double> ambientIllumination = multiplyVectors(intensity, this->ambientReflex);
        std::vector<double> diffusionIllumination = multiplyByScalar(multiplyVectors(intensity, this->diffuseReflex), diffusionFactor);
        std::vector<double> specularIllumination = multiplyByScalar(multiplyVectors(intensity, this->specularReflex), specularFactor);

        illumination = plusVectors(ambientIllumination, plusVectors(diffusionIllumination, specularIllumination));
        for (int i = 0; i < 3; i++)
        {
            if (illumination[i] > 1)
            {
                illumination[i] = 1;
            }
        }
        //std::cout << illumination[0] << " " << illumination[1] << " " << illumination[2] << " " << std::endl;
    }
    else
    {
        illumination.resize(3, -2);
    }


    return illumination;

}


