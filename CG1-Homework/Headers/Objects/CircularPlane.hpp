#ifndef CircularPlane_HPP
#define CircularPlane_HPP
#include "Plane.hpp"

class CircularPlane : public Plane
{
	public:
		double radius;

		CircularPlane(double radius, std::vector<double> center, std::vector<double> normal, double constAttenuation, double linearAttenuation,
			double quadraticAttenuation, std::vector<double> ambientReflex,
			std::vector<double> diffuseReflex, std::vector<double> specularReflex, int shininess);
		std::optional<std::vector<double>> doesItIntercept(Ray Ray);
		std::vector<double> Illumination(Ray Ray, std::vector<double> intensity);  
};

#endif