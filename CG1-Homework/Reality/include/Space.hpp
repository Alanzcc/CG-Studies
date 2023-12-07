#ifndef Space_HPP
#define Space_HPP

#include "../Algebra/include/Vec3.hpp"
#include "../Algebra/include/Ray.hpp"
#include "../Lights/include/Light.hpp"
#include "../Lights/include/Intensity.hpp"
#include "../Objects/include/Object.hpp"

#include "SDL_Pixels.h"

#include <vector>
#include <optional>
#include <utility>
#include <initializer_list>

class Space
{
    public:

        // Elements and ambient color
        std::vector<Object*> obj_list;
        std::vector<Light*> light_list;
        Intensity ambient_color;

        // Constructors
        Space();
        Space(std::initializer_list<Object*> obj_list);
        Space(std::initializer_list<Object*> obj_list, std::initializer_list<Light*> light_list);

        // Add objects and lights
        void add_object(Object* object);
        void add_light(Light* light);

        // Set/change ambient color
        void set_ambient_color(Intensity ambient_color);

        // Calculate the object that is intersected by the ray and return the color of the object at the intersection point
        std::optional<IntCol> intercept(const Ray& Ray) const;
        Intensity lighting_intensity(Object &obj, IntCol& inter_point, Ray& Eye) const;
        

}


#endif
