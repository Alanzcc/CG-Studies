#ifndef Canvas_HPP
#define Canvas_HPP

#include <vector>

#include "../Algebra/include/Ray.hpp"
#include "../Algebra/include/Vec3.hpp"
#include "../Algebra/include/Mat4.hpp"
#include "../Objects/include/Object.hpp"

#include "SDL.h"
#include "SDL_pixels.h"
#include "SDL_rect.h"
#include "SDL_video.h"



class Canvas
{
    public:
        const size_t width;
        const size_t height;
        
        const size_t pov_width;
        const size_t pov_height;

        size_t get_width() const;
        size_t get_height() const;
        size_t get_pov_width() const;
        size_t get_pov_height() const;

  // setters
  void set_pov_width(size_t);
  void set_pov_height(size_t);
  void set_pixel(SDL_Point, SDL_Color);

};

#endif