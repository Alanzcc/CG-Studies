#include "Ray.hpp"

Ray::Ray(std::vector<double> initialPoint, std::vector<double> direction)
{
    this->initialPoint = initialPoint;
    this->direction = normalize(initialPoint - direction);
}