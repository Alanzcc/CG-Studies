#include "../include/Canvas.hpp"


// Constructors

Canvas::Canvas(size_t w, size_t h, size_t pw, size_t ph, SDL_Color bgc)
    : width{w}, height{h}, pov_width{pw}, pov_height{ph}, bg_color{bgc},
      pixels{std::map<SDL_Color, std::vector<SDL_Point>>()}, window{nullptr}, renderer{nullptr}
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

// Get sizes
size_t Canvas::get_width() const { return width; }
size_t Canvas::get_height() const { return height; }
size_t Canvas::get_pov_width() const { return pov_width; }
size_t Canvas::get_pov_height() const { return pov_height; }

// Setters for pixel and background color
void Canvas::set_pixel(SDL_Color color, SDL_Point point) {
  pixels[color].push_back(point);
}

void Canvas::change_bg_color(SDL_Color color) {
  bg_color = color;
}

// Zoom in and out
void Canvas::zoom_in(double x) {
  pov_width = static_cast<size_t>(pov_w / x);
  pov_height = static_cast<size_t>(pov_h / x);
}
void Canvas::zoom_out(double x) {
  pov_width = static_cast<size_t>(pov_w * x);
  pov_height = static_cast<size_t>(pov_h * x);
}

// Keyboard actions
enum class ApplicationState {RUNNING, QUITTING};

ApplicationState keyboard_action() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_QUIT:
        return ApplicationState::QUITTING;
      case SDL_KEYDOWN:
        switch (event.key.keysym.sym) {
          case SDLK_ESCAPE:
            return ApplicationState::QUITTING;
          case SDLK_q:
            return ApplicationState::zoom_out(1.1);
          case SDLK_e:
            return ApplicationState::zoom_out(1.1);
        }
    }
  }
  return ApplicationState::RUNNING;
}

// Draw the canvas
void Canvas::render() {
  SDL_SetRenderDrawColor(renderer, bg_color.r, bg_color.g, bg_color.b, bg_color.a);
  SDL_RenderClear(renderer);
  for (auto& duo : pixels) {
    SDL_SetRenderDrawColor(renderer, duo.first.r, duo.first.g, duo.first.b, duo.first.a);
    SDL_RenderDrawPoints(renderer, duo.second.data(), duo.second.size());
  }
  SDL_RenderPresent(renderer);

  ApplicationState state = ApplicationState::RUNNING;
  while (state == ApplicationState::RUNNING) {
    state = keyboard_action();
  }
}