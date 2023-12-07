#include "../include/Space.hpp"


// Constructors
Space::Space() : obj_list{std::vector<Object *>()}, light_list{std::vector<Light *>()}, ambient_color{1, 1, 1} {}
Space::Space(std::initializer_list<Object *> ol) : obj_list{std::vector<Object *>(ol)}, ambient_color{1, 1, 1} {}
Space::Space(std::initializer_list<Object *> ol, std::initializer_list<Light *> ll) : obj_list{std::vector<Object *>(ol)},
                                                                                      light_list{std::vector<Light *>(ll)}, ambient_color{1, 1, 1} {}
// Add objects and lights
void Space::add_object(Object *object) { obj_list.push_back(object); }
void Space::add_light(Light *light) { light_list.push_back(light); }

// Set/change ambient color
void Space::set_ambient_color(Intensity color) { ambient_color = color; }

// Calculate the object that is intersected by the ray and return the color of the object at the intersection point
std::optional<IntCol> Space::intercept(const Ray &Ray)
{
    Object *closest_obj = nullptr;
    std::optional<IntCol> closest_intercept = std::nullopt;
    double min_dist = INFINITY;
    for (auto obj : obj_list)
    {
        std::optional<IntCol> intercepted = obj->intercept(Ray);
        if (intercepted.has_value() && intercepted.first.norm() < distance)
        {
            closest_obj = obj;
            closest_intercept = std::move(intercepted);
            min_dist = intercepted.first.norm();
        }
    }
    if (closest_obj == nullptr)
        return {};
    
    SDL_Color final_color = lighting_intensity(*closest_obj, * closest_intercept, Ray).convert_to_SDL_Color();
    return std::make_pair(closest_intercept.first, final_color);
}

// Calculate the color of the object at the intersection point
Intensity Space::lighting_intensity(Object &obj, IntCol &inter_point, Ray &Eye) const
{
    Intensity final_int = ambient_color * obj.get_ambient_color();
    for (auto light : light_list)
        final_int = final_int + light->lighting(inter_obj, objs, intersection, Eye);
    return final_int;
}