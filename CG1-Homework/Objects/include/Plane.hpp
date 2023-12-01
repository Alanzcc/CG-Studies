#ifndef Plane_HPP
#define Plane_HPP

#include "Object.hpp"

class Plane : public Object
{
	public:
		Point center;
		Vec3 normal;
		Intensity ambientReflex;
		Intensity diffuseReflex;
		Intensity specularReflex;
		double shininess;

		Plane(Point center, Vec3 normal, Intensity ambientReflex, Intensity diffuseReflex, Intensity specularReflex, double shininess);

		std::optional<IntCol> intercept(Ray &Ray) override;
		std::optional<Vec3> get_normal (const Vec3 &intersection) override;
		Intensity get_emissive_color() override;
		Intensity get_ambient_color() override;
		Intensity get_diffuse_color() override;
		Intensity get_specular_color() override;
		double get_shininess() override;

		/*Plane(Vec3 center, Vec3 normal, Vec3 ambientReflex,
		Vec3 diffuseReflex, Vec3 specularReflex, int shininess);
		std::optional<Vec3>doesItIntercept(Ray Ray);
		Vec3 Illumination(Ray Ray, Vec3 intensity);*/
};



#endif
