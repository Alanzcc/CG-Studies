#include "Sphere.hpp"


Sphere::Sphere(double radius, std::vector<double> center, std::vector<double> ambientReflex,
                std::vector<double> diffuseReflex, std::vector<double> specularReflex,
                int specularExponent)
                {
                    this->radius = radius;
                    this->center = center;
                    this->ambientReflex = ambientReflex;
                    this->diffuseReflex = diffuseReflex; 
                    this->specularReflex = specularReflex;
                    this->specularExponent = specularExponent;
                }

std::optional<std::vector<double>> doesItIntercept()
{
    std::vector<double> w = {Ray.initialPoint[0] - center[0], Ray.initialPoint[1] - center[1], Ray.initialPoint[2] - center[2]};
    double b = dotProduct(w, Ray.direction);
    double c = dotProduct(w, w) - this->radius * this->radius;
    double delta = b * b - 4 * c;

    if (delta < 0)
    {
        return {}
    }
    double x1 = (b - sqrt(delta)) / 2;
    double x2 = (b + sqrt(delta)) / 2;
    double intersectionScalar = std::min(x1, x2);
    std::vector<double> intersectionPoint = plusVectors(Ray.initialPoint, multiplyByScalar(Ray.direction, intersectionScalar));
    return intersectionPoint;
}

std::vector<double> ilumination(Ray Ray, intensity)
{
    std::vector<double> interPoint = doesItIntercept();
    
    std::vector<double> light = normalize(minus(Ray.initialPoint, interPoint));

    std::vector<double> normal = normalize(divideByScalar(minusVectors(interPoint, center), radius));

    std::vector<double> reflected = minus(multiplyByScalar(normal, 2 * dotProduct(light, normal)), light);

    std::vector<double> vision = multiplyByScalar(normalize(minusVectors(interPoint, Ray.initialPoint)), -1); // While cam = ray_source
    
    double diffusionFactor = dotProduct(light, normal);
    double specularFactor = pow(dotProduct(reflected, vision), specularExponent);

    std::vector<double> ambientIllumination = multiplyVectors(intensity, ambientReflex);
    std::vector<double> diffusionIllumination = multiplyByScalar(multiplyVectors(intensity, diffuseReflex), diffusionFactor);
    std::vector<double> specularIllumination = multiplyByScalar(multiplyVectors(intensity, specularReflex), specularFactor);

    std::vector<double> illumination = plusVectors(ambientIllumination, plusVectors(diffusionIllumination, specularIllumination));
    
    return illumination;

}



