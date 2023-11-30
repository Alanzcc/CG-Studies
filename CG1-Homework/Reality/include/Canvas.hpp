#ifndef Canvas_HPP
#define Canvas_HPP

#include <vector>

#include "../Algebra/include/Ray.hpp"

class Canvas
{
    public:
        int windowWidth, windowHeight, windowDistance, numLines,
        numColumns, windowMinX, windowMaxY;
        double  deltaX, deltaY;

        Canvas(int windowWidth, int windowHeight, int windowDistance,
        int numLines, int numColumns);
        std::vector<std::vector<std::vector<double>>> Raycast(Sphere Sphere, std::vector<double> lightSource, std::vector<double> intensity);
};

#endif