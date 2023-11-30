#ifndef Point_HPP
#define Point_HPP

#include "Vec3.hpp"
#include <vector>

class Point
{
public:

	double x;
	double y;
	double z;

	// Constructors
	Point();
	Point(const Vec3&);
	Point(std::vector<double>& other);
	Point(double a, double b, double c);

	// Operations

	Vec3 operator*(const Point& rhs) const;
	Vec3 operator*(double scalar) const;

	Vec3 operator/ (const Point& rhs) const;
	Vec3 operator/ (double scalar) const;

	Vec3 operator+(const Point& rhs) const;
	Vec3 operator+(double scalar) const;

	Vec3 operator-(const Point& rhs) const;
	Vec3 operator-(double scalar) const;

	explicit operator Vec3() const;
};


#endif