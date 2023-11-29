#include "./Headers/Lights/Point_Light.hpp"


Point_Light::Point_Light(Point o, Vector di, Intensity lc, Point de) : origin{ o }, direction{ di }, light_color{ lc }, decay{ de.x, de.y, de.z } {}
 
Intensity Point_Light::lighting(const Object& inter_obj, std::vector<Object*> objs, const Vector& intersection, const Ray& Eye) const
{
	Vector light = (origin - intersection);
	double light_length = light.norm();

	light = light.normalize();

	Ray light_ray(origin, intersection);
	for (auto& obj : objs)
	{
		if (obj != &inter_obj)
		{
			auto other_inter = obj->intercept(light_ray);
			if (other_inter.has_value())
			{
				Vector other_inter_vector = (other_inter - origin);
				double other_inter_length = other_inter_vector.norm();
				if (light_length >= other_inter_length)
					return { 0, 0, 0 };
			}

		}
	}

	Vector normal = inter_obj.get_normal(intersection);
	if (!normal.has_value())
		return { 0, 0, 0 };

	Vector view = -Eye.get_direction();
	Vector reflection = normal * (2 * normal.dot(view)) - view;

	Intensity diffuse_term = (inter_obj.get_diffuse_color() * light_color) * std::max(normal.dot(light), 0.0);

	double shininess = inter_obj.get_shininess();

	Vector half_angle = (light + view).normalize();

	double facing = 0;
	if (normal.dot(light) > 0)
		facing = 1;
		
	Intensity specular_term = inter_obj.get_specular_color() * light_color * facing * std::pow(std::max(normal.dot(half_angle), 0.0), shininess);
	
	double attenuation = (decay.x * std::pow(light_length, 2)) + (decay.y * light_length) + decay.z;

	return (diffuse_term + specular_term) / attenuation;
}