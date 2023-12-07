#ifndef Canvas_HPP
#define Canvas_HPP

#include <vector>
#include <map>
#include <cstddef>

#include "SDL.h"
#include "SDL_pixels.h"
#include "SDL_rect.h"
#include "SDL_video.h"



class Canvas
{
    public:
        // Screen parameters
        const size_t width;
        const size_t height;
        size_t pov_width;
        size_t pov_height;
        SDL_Color bg_color;
        std::map<SDL_Color, std::vector<SDL_Point>> pixels;
        SDL_window* window;
        SDL_Renderer* renderer;

        // Constructors
        Canvas(size_t width, size_t height, size_t pov_width, size_t pov_height, SDL_Color bg_color);
        Canvas(size_t width, size_t height, SDL_Color bg_color);
        Canvas(size_t width, size_t height);
        Canvas(Canvas &&other);

        // Get sizes
        size_t get_width() const;
        size_t get_height() const;
        size_t get_pov_width() const;
        size_t get_pov_height() const;
        SDL_Color get_bg_color() const;

        // Setters for pixel and background color
        void set_pixel(SDL_Color color, SDL_Point point);
        void change_bg_color(SDL_Color color);

        // Zoom in and out
        void zoom_in(double x);
        void zoom_out(double x);
        // Draw the canvas
        void paint() const;

};

#endif