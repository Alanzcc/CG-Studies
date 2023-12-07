#include "../Reality/include/Canvas.hpp"
#include "../Reality/include/Space.hpp"
#include "../Algebra/include/Vec3.hpp"
#include "../Algebra/include/Point.hpp"
#include "../Algebra/include/Ray.hpp"
#include "../Lights/include/Intensity.hpp"
#include "../Lights/include/Directional_Light.hpp"
#include "../Lights/include/Point_Light.hpp"
#include "../Lights/include/Spotlight.hpp"
#include "../Objects/include/Sphere.hpp"

#include <iostream>
#include <vector>
#include "../Reality/include/Canvas.hpp"
#include "../Reality/include/Space.hpp"
#include "../Algebra/include/Vec3.hpp"
#include "../Algebra/include/Point.hpp"
#include "../Algebra/include/Ray.hpp"
#include "../Lights/include/Intensity.hpp"
#include "../Lights/include/Directional_Light.hpp"
#include "../Lights/include/Point_Light.hpp"
#include "../Lights/include/Spotlight.hpp"
#include "../Objects/include/Sphere.hpp"

#include <iostream>
#include <vector>

const size_t WIN_WIDTH = 500;
const size_t WIN_HEIGHT = 500;

int main() {
    auto canvas = new Canvas(WIN_WIDTH, WIN_HEIGHT);
    double canvas_dist = 30;

    // create ball
    double radius = 40;
    Point center{ 0, 0, -100 };
    SDL_Color color{ 0, 0, 0, 255 };
    //Intensity ball_k{0.7, 0.2, 0.2};
    auto red_ball = new Sphere(center, radius);

    /*
      //Intensity no_ambient{0, 0, 0};

      // create planes

        Intensity floor_k{0.2, 0.7, 0.2};
        SDL_Color floor_color = {0, 0, 0, 255};
        Plane *floor = new Graphite::Plane(
          {0, -radius, 0}, {0, 1, 0}, floor_color, 1, floor_k, floor_k, no_ambient);

      Graphite::Light::Intensity wall_k{0.3, 0.3, 0.7};
      SDL_Color wall_color = {0, 0, 0, 255};
      Graphite::Plane *wall = new Graphite::Plane(
          {0, 0, -200}, {0, 0, 1}, wall_color, 1, wall_k, wall_k, no_ambient);
    */

    // create light
    auto light = new Point_Light({ 0, 60, -30 }, { 0.7, 0.7, 0.7 });
    light->set_decay(1e-5, 6e-3, 0.1);

    // create space
    auto objs = Space();
    objs.set_ambient_light({ 0.3, 0.3, 0.3 });
    objs.add_object(red_ball);
    //objs.add_obj(floor);
    //objs.add_obj(wall);
    objs.add_light(light);
    auto scene = Graphite::Scene(&objs);
    scene.set_bg_color({255, 255, 255, 255});

    // render
    canvas.render();
    return 0;

}
