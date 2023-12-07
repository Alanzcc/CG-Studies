/*
#ifndef Quaternion_HPP
#define Quaternion_HPP

#include <cmath>

#include "Mat4.hpp"
#include "Vec3.hpp"
#include "Point.hpp"
class Quaternion
{
    public:
        double s;
        double x;
        double y;
        double z;

        Quaternion(double scalar, double x, double y, double z);
        Quaternion(double scalar, const Vec3 &vec);
        Quaternion(double scalar, const Point &point);

        double norm() const;
        double dot(const Quaternion &rhs) const;
        Quaternion cross(const Quaternion &rhs) const;
        Quaternion normalize() const;
        Quaternion conjugate() const;
        
        Quaternion operator* (const Quaternion &rhs) const; 
        Quaternion operator* (double scalar) const; 
        Vec3 operator* (const Vec3 &rhs) const;

        Quaternion operator/ (double scalar) const; 
        
        Quaternion operator+ (const Quaternion &rhs) const; 
        Quaternion operator+ (double scalar) const;

        Quaternion operator- (const Quaternion &rhs) const; 
        Quaternion operator- (double scalar) const;
};

#endif

*/