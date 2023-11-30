
#include "../include/Objects/Plane.hpp"

Plane::Plane(std::vector<double> center, std::vector<double> normal, double constAttenuation, double linearAttenuation,
             double quadraticAttenuation, std::vector<double> ambientReflex, std::vector<double> diffuseReflex,
             std::vector<double> specularReflex, int shininess)
{
    this->center = center;
    this->normal = normalize(normal);
    
    this->constAttenuation = constAttenuation;
    this->linearAttenuation = linearAttenuation;
    this->quadraticAttenuation = quadraticAttenuation;
    this->ambientReflex = ambientReflex;
    this->diffuseReflex = diffuseReflex;
    this->specularReflex = specularReflex;
    this->shininess = shininess;
}

std::optional<std::vector<double>> Plane::doesItIntercept(Ray Ray)
{
    std::vector<double> w = minusVectors(this->center, Ray.initialPoint);
    double denominator = dotProduct(Ray.direction, this->normal);
    if (denominator == 0)
    {
        return {};
    }
    double intersectionScalar = dotProduct(w, this->normal) / denominator;
    if (intersectionScalar <= 0)
    {
        return {};
    }
    std::vector<double> intersectionPoint = plusVectors(Ray.initialPoint, multiplyByScalar(Ray.direction, intersectionScalar));
    return intersectionPoint;
}

std::vector<double> Plane::Illumination(Ray Ray, std::vector<double> intensity)
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
    }
    else
    {
        illumination.resize(3, -2);
    }

    return illumination;

}
