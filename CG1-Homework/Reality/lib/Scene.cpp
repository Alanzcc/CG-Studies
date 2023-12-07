#include "../include/Scene.hpp"

Camera::Camera() : origin{0, 0, 0}, x_axis{1, 0, 0}, y_axis{0, 1, 0}, z_axis{0, 0, 1} {}
Camera(const Point &origin, const Point &look_at, const Point &up) : origin{origin}, z_axis{(origin - look_at).normalize()}
{
    x_axis = (up.cross(z_axis)).normalize();
    y_axis = z_axis.cross(x_axis);
}

// getters
const Vec3 &x_axis() const { return x_axis; }
const Vec3 &y_axis() const { return y_axis; }
const Vec3 &z_axis() const { return z_axis; }
const Point3 &origin() const { return origin; }

Scene::Scene(Space *s) : space{s}, bg_color{} {}

Space &Scene::get_space() { return *space; }
std::optional<SDL_Color> Scene::get_bg_color() const { return bg_color; }

void Scene::set_bg_color(const SDL_Color &bgc) { bg_color = bgc; }
void Scene::set_camera(const Camera &eye) { camera = eye; }
void Scene::set_pov(Camera &&pov) { camera = std::move(pov); }

void Scene::render(Canvas canvas, double depth)
{
    const size_t pov_width = canvas.get_pov_width();
    const size_t pov_height = canvas.get_pov_height();
    const SDL_Color bg_color = canvas.get_bg_color();
    const double half_width = static_cast<double>(pov_width) / 2;
  const double half_height = static_cast<double>(pov_height) / 2;
  const double delta_x = pov_width / static_cast<double>canvas.get_width();
  const double delta_y = pov_height / static_cast<double> canvas.get_height();
  const double hdx = delta_x / 2;
  const double hdy = delta_y / 2;

  for (size_t i = 0; i < canvas.get_width(); ++i) {
    const double x = static_cast<double>(i) * delta_x - half_width + hdx;
    for (size_t j = 0; j < canvas.get_height(); ++j) {
        const double y = static_cast<double>(j) * delta_y - half_height + hdy;

        Ray *c_ray;
        Point end = {x, y, -depth};
        c_ray = new Ray(camera.get_origin(), end);

        std::optional<IntCol> int_col = space->intersect(*c_ray);
        SDL_Color color = (int_col.has_value()) ? int_col->second : bg_color;
        canvas.set_pixel(*color, {static_cast<int>i, static_cast<int>j});
    }
  }
}


