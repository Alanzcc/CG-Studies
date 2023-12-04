#ifndef Quaternion_HPP
#define Quaternion_HPP

#include "Mat4.hpp"

class Quaternion
{
    public:
        Quaternion();
        Quaternion(Mat4 &other);
        
        double dot(const Quaternion &rhs) const;
        double norm() const;
        Quaternion normalize() const;
        Quaternion conjugate() const;
        
        Quaternion operator* (const Quaternion &rhs) const; 
        Mat4 operator* (Mat4 &rhs) const; 

        Quaternion operator/ (const Quaternion &rhs) const;
        Mat4 operator/ (Mat4 &rhs) const; 
        
        Quaternion operator+ (const Quaternion &rhs) const; 
        Mat4 operator+ (Mat4 &rhs) const;

        Quaternion operator- (const Quaternion &rhs) const; 
        Mat4 operator- (Mat4 &rhs) const;
};

#endif