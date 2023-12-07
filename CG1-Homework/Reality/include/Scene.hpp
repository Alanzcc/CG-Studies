#ifndef Scene'_HPP
#define Scene_HPP

#include "Space.hpp"
#include "../Algebra/include/Point.hpp"
#include "../Algebra/include/Vec3.hpp"
#include "../Algebra/include/Mat4.hpp"

#include <SDL_pixels.h>
#include <SDL_rect.h>

#include <optional>
#include <utility>

enum Projection { PERSPECTIVE, ORTHOGRAPHIC, OBLIQUE };

class Camera
{
    private: 
        Point origin;
        Vec3 x_axis;
        Vec3 y_axis;
        Vec3 z_axis;
    public:
        Camera();
        Camera(const Point &origin, const Point &look_at, const Point &up);
    
        const Vec3 &get_x_axis() const;
        const Vec3 &get_y_axis() const;
        const Vec3 &get_z_axis() const;
        const Point &get_origin() const;
};

class Scene
{
    private:
        Space *space;
        std::optional<SDL_Color> bg_color;
        Camera camera;
        //Projection projection;
        //double near;
        //double far;
        //double fov;

    public: 
        Scene(Space *);

        Space &get_space();
        std::optional<SDL_Color> get_bg_color() const;

        void set_bg_color(const SDL_Color &bgc);
        void set_camera(const Camera &eye);
        void set_pov(Camera &&pov);
        //void set_projection(Projection);
        //void set_near();
        //void set_far();
        //void set_fov();

        void render(Canvas canvas, double depth);
        
}

#endif