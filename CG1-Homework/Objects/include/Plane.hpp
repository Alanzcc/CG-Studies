#ifndef Plane_HPP
#define Plane_HPP

#include "Object.hpp"

class Plane : public Object
{
public:
	Point center;
	Vec3 normal;
	Intensity emissive_color;
	Intensity ambient_color;
	Intensity diffuse_color;
	Intensity specular_color;
	double shininess;

	Plane(Point center, Vec3 normal, Intensity emissive_color, Intensity ambient_color, Intensity diffuse_color, Intensity specular_color, double shininess);

	std::optional<IntCol> intercept(const Ray& Ray) const override;
	std::optional<Vec3>get_normal(const Point& intersection) const override;
	Intensity get_emissive_color() const override;
	Intensity get_ambient_color() const override;
	Intensity get_diffuse_color() const override;
	Intensity get_specular_color() const override;
	double get_shininess() const override;
};



#endif
