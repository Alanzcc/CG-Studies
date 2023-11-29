#ifndef Point_HPP
#define Point_HPP

#include "Vector.hpp"
#include <vector>

class Point
{
public:

	double x;
	double y;
	double z;

	// Constructors
	Point();
	Point(const Vector&);
	Point(std::vector<double>& other);
	Point(double a, double b, double c);

	// Operations

	Vector operator*(const Point& rhs) const;
	Vector operator*(double scalar) const;

	Vector operator/ (const Point& rhs) const;
	Vector operator/ (double scalar) const;

	Vector operator+(const Point& rhs) const;
	Vector operator+(double scalar) const;

	Vector operator-(const Point& rhs) const;
	Vector operator-(double scalar) const;

	explicit operator Vector() const;
};


#endif