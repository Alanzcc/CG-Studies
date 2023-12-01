#include "../include/Canvas.hpp"


Canvas::Canvas(size_t w, size_t h, size_t pw, size_t ph, SDL_Color bgc)
    : width{w}, height{h}, pov_width{pw}, pov_height{ph}, bg_color{bgc},
      pixels{std::map<SDL_Color, std::vector<SDL_Point> >()}, window{nullptr}, renderer{nullptr}
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_CreateWindowAndRenderer(width, height, 0, &window, &renderer);
}
    
Canvas::Canvas(size_t w, size_t h, size_t pw, size_t ph, SDL_Color bgc)
    : width{w}, height{h}, pov_width{60}, pov_height{60}, bg_color{bgc},
      pixels{std::map<SDL_Color, std::vector<SDL_Point>>()}, window{nullptr}, renderer{nullptr}
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_CreateWindowAndRenderer(width, height, 0, &window, &renderer);
}

Canvas::Canvas(size_t w, size_t h)
    : width{w}, height{h}, pov_width{60}, pov_height{60}, bg_color{0,0,0,255},
      pixels{std::map<SDL_Color, std::vector<SDL_Point>>()}, window{nullptr}, renderer{nullptr}
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_CreateWindowAndRenderer(width, height, 0, &window, &renderer);
}

Canvas::Canvas(Canvas &&other)
    : width{other.get_width()}, height{other.get_height()},
      pov_width{other.get_pov_width()}, pov_height{other.get_pov_height()},
      bg_color{std::move(other.bg_color)}, pixels{std::move(other.pixels)} {
  other.window = nullptr;
  other.renderer = nullptr;
}

size_t Canvas::get_width() const { return width; }
size_t Canvas::get_height() const { return height; }
size_t Canvas::get_pov_width() const { return pov_width; }
size_t Canvas::get_pov_height() const { return pov_height; }

void Canvas::set_pixel(SDL_Color color, SDL_Point point) {
  pixels[color].push_back(point);
}

void Canvas::change_bg_color(SDL_Color color) {
  bg_color = color;
}

void Canvas::zoom_in(double x) {
  pov_width = static_cast<size_t>(pov_w / x);
  pov_height = static_cast<size_t>(pov_h / x);
}
void Canvas::zoom_out(double x) {
  pov_width = static_cast<size_t>(pov_w * x);
  pov_height = static_cast<size_t>(pov_h * x);
}
