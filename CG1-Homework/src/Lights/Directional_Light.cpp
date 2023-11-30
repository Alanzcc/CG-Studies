#include "../include/Lights/Directional_Light.hpp"

Directional_Light::Directional_Light(Vec3 d, Intensity lc) : direction{ d.normalize()}, light_color{lc} {}

Intensity Directional_Light::lighting(const Object &inter_obj, std::vector<Object*> objs, const Vec3& intersection, const Ray& Eye) const
{

	// Luz direcional é caracterizada por não ter origem e distância infinita
	Vec3 light = -direction;
	double light_length = 0;
	

	Ray light_ray(intersection, - direction);
	for (auto& obj : objs)
	{
		if (obj != &inter_obj)
		{
			auto other_inter = obj->intercept(light_ray);
			if (other_inter.has_value())
			{
				Vec3 other_inter_vector = (other_inter - intersection);
				double other_inter_length = other_inter_vector.norm();
				if (light_length >= other_inter_length)
					return { 0, 0, 0 };
			}
		}
	}

	Vec3 normal = inter_obj.get_normal(intersection);
	if (!normal.has_value())
		return { 0, 0, 0 };

	Vec3 view = -Eye.get_direction();
	Vec3 reflection = normal * (2 * normal.dot(view)) - view;

	Intensity diffuse_term = (inter_obj.get_diffuse_color() * light_color) * std::max(normal.dot(light), 0.0);

	double shininess = inter_obj.get_shininess();
	//double revi = reflection.dot(vision);
	
	Vec3 half_angle = (light + view).normalize();
	
	double facing = 0;
	if (normal.dot(light) > 0)
		facing = 1;

	Intensity specular_term = inter_obj.get_specular_color() * light_color * facing * std::pow(std::max(normal.dot(half_angle), 0.0), shininess);

	return diffuse_term + specular_term;
}