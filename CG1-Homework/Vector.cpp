#include "Vector.hpp"

// Constructors
Vector::Vector() : x{0}, y{0}, z{0} {}
Vector::Vector(std::vector<double> &other) :  x{other[0]}, y{other[1]}, z{other[2]} {}
Vector::Vector(double a, double b, double c) : x{a}, y{b}, z{c} {}

// Vector shenanigans

double Vector::norm() const { return std::sqrt(x*x + y*y + z*z); }

Vector Vector::normalize() const { return (*this) / this->norm(); }

double Vector::dot(const Vector &other) const { return (x * other.x + y * other.y + z * other.z); }

Vector Vector::cross(const Vector& other) const
{ return { y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x }; }

// Operations

Vector Vector::operator* (const Vector& rhs) const
{ return { x * rhs.x, y * rhs.y, z * rhs.z }; }

Vector Vector::operator* (double scalar) const
{ return { x * scalar, y * scalar, z * scalar }; }

Vector Vector::operator/ (const Vector& rhs) const
{ return { x / rhs.x, y / rhs.y, z / rhs.z }; }

Vector Vector::operator/ (double scalar) const
{ return { x / scalar, y / scalar, z / scalar }; }

Vector Vector::operator+ (const Vector& rhs) const
{ return { x + rhs.x , y + rhs.y, z + rhs.z };  }

Vector Vector::operator+ (double scalar) const
{ return { x + scalar , y + scalar, z + scalar }; }

Vector Vector::operator- (const Vector& rhs) const
{ return { x - rhs.x , y - rhs.y, z - rhs.z }; }

Vector Vector::operator- (double scalar) const
{ return { x - scalar , y - scalar, z - scalar }; }

Vector Vector::operator- () const
{ return { -x , -y, -z }; }







