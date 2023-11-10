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

// Fix issue with return type
std::optional<std::vector<double>> Sphere::doesItIntercept(Ray Ray)
{
    std::vector<double> w = minusVectors(Ray.initialPoint, center);
    double b = (2 * dotProduct(w, Ray.direction));
    //printf("b is: %f\n ", b);
    double c = dotProduct(w, w) - (this->radius * this->radius);
    //printf("c is: %f\n ", c);
    double delta = (b * b) - (4 * c);
    //printf("Delta is: %f\n ", delta);
    if (delta < 0)
    {
        return {};
    }
    double x1 = (b - sqrt(delta)) / 2;
    double x2 = (b + sqrt(delta)) / 2;
    double intersectionScalar = std::min(x1, x2);
    std::vector<double> intersectionPoint = plusVectors(Ray.initialPoint, multiplyByScalar(Ray.direction, intersectionScalar));
    //printf("intersectionPoint: %f %f %f\n", intersectionPoint[0], intersectionPoint[1], intersectionPoint[2]);
    return intersectionPoint;
}

std::vector<double> Sphere::Illumination(Ray Ray, std::vector<double> intensity) // Still need to ready intensity
{
    std::vector<double> illumination;
    std::vector<double> interPoint = doesItIntercept(Ray).value_or(std::vector<double>(3, -2));
    //printf("interPoint: %f %f %f\n", interPoint[0], interPoint[1], interPoint[2]);
    if (interPoint[0] != -2)
    {
        std::vector<double> light = normalize(minusVectors(Ray.initialPoint, interPoint));

        std::vector<double> normal = normalize(divideByScalar(minusVectors(interPoint, this->center), this->radius));

        std::vector<double> reflected = minusVectors(multiplyByScalar(normal, 2 * dotProduct(light, normal)), light);

        std::vector<double> vision = multiplyByScalar(normalize(minusVectors(interPoint, Ray.initialPoint)), -1); // While cam = ray_source

        double diffusionFactor = dotProduct(light, normal);
        double specularFactor = pow(dotProduct(reflected, vision), this->specularExponent);

        std::vector<double> ambientIllumination = multiplyVectors(intensity, this->ambientReflex);
        std::vector<double> diffusionIllumination = multiplyByScalar(multiplyVectors(intensity, this->diffuseReflex), diffusionFactor);
        std::vector<double> specularIllumination = multiplyByScalar(multiplyVectors(intensity, this->specularReflex), specularFactor);

        illumination = plusVectors(ambientIllumination, plusVectors(diffusionIllumination, specularIllumination));
    }
    else
    {
        illumination.resize(3, -2);
    }

    return illumination;

}



