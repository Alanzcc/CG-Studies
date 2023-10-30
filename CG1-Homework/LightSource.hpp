#ifndef LightSource_HPP
#define LightSource_HPP

#include "Ray.hpp"
#include <vector>

class LightSource
{
    public:
        std::vector<double> intensity;

        LightSource(std::vector<double> intensity);
        
}
#endif