#include "../include/Intensity.hpp"

Intensity::Intensity(double r, double g, double b)
{
	if ((r < 0 || r > 1) || (g < 0 || g > 1) || (b < 0 || b > 1))
		throw std::invalid_argument("One or more RGB values smaller than 0 or greater than 1");
	red = r;
	green = g;
	blue = b;
}

Intensity::Intensity(const SDL_Color& rgb) : red{static_cast<double>(rgb.r) / 255.0}, green{static_cast<double>(rgb.g) 255.0}, blue{static_cast<double>(rgb.b)255.0} {}

std::initializer_list<int> Intensity::convert_to_SDL_Color() const
{
	return { static_cast<int>(red * 255), static_cast<int>(green * 255), static_cast<int>(blue * 255) };
}

Intensity Intensity::operator* (const Intensity& rhs) const
{
	auto new_red = std::clamp<double>(red * rhs.red, 0, 1);
	auto new_green = std::clamp<double>(green * rhs.green, 0, 1);
	auto new_blue = std::clamp<double>(blue * rhs.blue, 0, 1);
	return { new_red, new_green, new_blue };
}

Intensity Intensity::operator*(double scalar) const
{
	auto new_red = std::clamp<double>(red * scalar, 0, 1);
	auto new_green = std::clamp<double>(green * scalar, 0, 1);
	auto new_blue = std::clamp<double>(blue * scalar, 0, 1);
	return { new_red, new_green, new_blue };
}

Intensity Intensity::operator/ (const Intensity& rhs) const
{
	auto new_red = std::clamp<double>(red / rhs.red, 0, 1);
	auto new_green = std::clamp<double>(green / rhs.green, 0, 1);
	auto new_blue = std::clamp<double>(blue / rhs.blue, 0, 1);
	return { new_red, new_green, new_blue };
}

Intensity Intensity::operator/ (double scalar) const
{
	auto new_red = std::clamp<double>(red / scalar, 0, 1);
	auto new_green = std::clamp<double>(green / scalar, 0, 1);
	auto new_blue = std::clamp<double>(blue / scalar, 0, 1);
	return { new_red, new_green, new_blue };
}

Intensity Intensity::operator+ (const Intensity& rhs) const
{
	auto new_red = std::clamp<double>(red + rhs.red, 0, 1);
	auto new_green = std::clamp<double>(green + rhs.green, 0, 1);
	auto new_blue = std::clamp<double>(blue + rhs.blue, 0, 1);
	return { new_red, new_green, new_blue };
}

Intensity Intensity::operator- (const Intensity& rhs) const
{
	auto new_red = std::clamp<double>(red - rhs.red, 0, 1);
	auto new_green = std::clamp<double>(green - rhs.green, 0, 1);
	auto new_blue = std::clamp<double>(blue - rhs.blue, 0, 1);
	return { new_red, new_green, new_blue };
}