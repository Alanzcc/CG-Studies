#ifndef Intensity_HPP
#define Intensity_HPP

#include <stdexcept>
#include <initializer_list>
#include <algorithm>

#include "SDL_pixels.h"

class Intensity
{
public:
	double red;
	double green;
	double blue;

	Intensity(double r, double g, double b);
	Intensity(const SDL_Color& rgb);
	std::initializer_list<int> convert_to_SDL_Color() const;
	Intensity operator*(const Intensity& rhs) const;
	Intensity operator*(double scalar) const;
	Intensity operator/(const Intensity& rhs) const;
	Intensity operator/(double scalar) const;
	Intensity operator+(const Intensity& rhs) const;
	Intensity operator-(const Intensity& rhs) const;
	operator SDL_Color() const;
};


#endif
