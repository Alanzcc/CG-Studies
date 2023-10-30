#ifndef Ray_H
#define Ray_H
#include <vector>

class Ray
{
    public:
        std::vector<double> initialPoint;
        std::vector<double> direction; // Must be a normalized vector

        Ray(std::vector<double> initialPoint, std::vector<double> direction);
};

#endif