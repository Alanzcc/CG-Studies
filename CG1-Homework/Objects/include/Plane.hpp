#ifndef Plane_HPP
#define Plane_HPP

#include "Object.hpp"

class Plane : public Object
{
	public:
		std::vector<double> center;
		std::vector<double> normal;

		Plane(std::vector<double> center, std::vector<double> normal, std::vector<double> ambientReflex,
		std::vector<double> diffuseReflex, std::vector<double> specularReflex, int shininess);
		std::optional<std::vector<double>>doesItIntercept(Ray Ray);
		std::vector<double> Illumination(Ray Ray, std::vector<double> intensity);
};



#endif
