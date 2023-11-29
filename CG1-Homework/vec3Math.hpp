#ifndef Vector_HPP
#define Vector_HPP

#include <vector>
#include <cmath>

class Vector
{
	public:

		double x;
		double y;
		double z;
		
		// Constructors
		Vector();
		Vector(std::vector<double> &other);
		Vector(double a, double b, double c);

		// Vector shenanigans
		double norm() const;
		Vector normalize() const;
		double dot(const Vector& other) const;
		Vector cross(const Vector& other) const;
		
		// Operations

		Vector operator* (const Vector& rhs) const; 
		Vector operator* (double scalar) const;

		Vector operator/ (const Vector& rhs) const;
		Vector operator/ (double scalar) const;
		
		Vector operator+ (const Vector& rhs) const;
		Vector operator+ (double scalar) const;

		Vector operator- (const Vector& rhs) const;
		Vector operator- (double scalar) const;
		Vector operator- () const;
};


#endif