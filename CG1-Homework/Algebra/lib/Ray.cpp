#include "../include/Ray.hpp"

Ray::Ray(Point o, Vec3 d) : origin {o}, direction{d.normalize()} {}
Ray::Ray(Point o, Point d) : origin{o}, direction{(d - o).normalize()} {}

Point Ray::get_origin() const { return origin; }
Vec3 Ray::get_direction() const { return direction; }