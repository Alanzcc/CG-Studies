#ifndef Vec3_HPP
#define Vec3_HPP

#include <vector>
#include <cmath>

class Vec3
{
	public:

		double x;
		double y;
		double z;
		
		// Constructors
		Vec3();
		Vec3(std::vector<double> &other);
		Vec3(double a, double b, double c);

		// Vec3 shenanigans
		double norm() const;
		Vec3 normalize() const;
		double dot(const Vec3& other) const;
		Vec3 cross(const Vec3& other) const;
		
		// Operations

		Vec3 operator* (const Vec3& rhs) const; 
		Vec3 operator* (double scalar) const;

		Vec3 operator/ (const Vec3& rhs) const;
		Vec3 operator/ (double scalar) const;
		
		Vec3 operator+ (const Vec3& rhs) const;
		Vec3 operator+ (double scalar) const;

		Vec3 operator- (const Vec3& rhs) const;
		Vec3 operator- (double scalar) const;
		Vec3 operator- () const;
};


#endif