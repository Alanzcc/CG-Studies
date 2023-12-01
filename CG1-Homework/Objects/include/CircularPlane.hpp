#ifndef CircularPlane_HPP
#define CircularPlane_HPP
#include "Plane.hpp"

class CircularPlane : public Plane
{
	public:
		double radius;
		Point center;
		Vec3 normal;
		Intensity ambientReflex;
		Intensity diffuseReflex;
		Intensity specularReflex;
		double shininess;

		Circular Plane(double radius, Point center, Vec3 normal, Intensity ambientReflex, Intensity diffuseReflex, Intensity specularReflex, double shininess);
		
		std::optional<IntCol> intercept(Ray &Ray) override;
		std::optional<Vec3> get_normal (const Vec3 &intersection) override;
		Intensity get_emissive_color() override;
		Intensity get_ambient_color() override;
		Intensity get_diffuse_color() override;
		Intensity get_specular_color() override;
		double get_shininess() override;
};

#endif