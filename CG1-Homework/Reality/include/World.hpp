#ifndef World_HPP
#define World_HPP

#include "../Algebra/include/Point.hpp"
#include "../Algebra/include/Vec3.hpp"
#include "../Algebra/include/Mat4.hpp"



enum Projection { PERSPECTIVE, ORTHOGRAPHIC, OBLIQUE };
class World
{
    public: 
        Point origin;
        Point x_axis;
        Point y_axis;
        Point z_axis;

        

};

#endif