#include "../include/Algebra/Vec3.hpp"

// Constructors
Vec3::Vec3() : x{0}, y{0}, z{0} {}
Vec3::Vec3(std::vector<double> &other) :  x{other[0]}, y{other[1]}, z{other[2]} {}
Vec3::Vec3(double a, double b, double c) : x{a}, y{b}, z{c} {}

// Vec3 shenanigans

double Vec3::norm() const { return std::sqrt(x*x + y*y + z*z); }

Vec3 Vec3::normalize() const { return (*this) / this->norm(); }

double Vec3::dot(const Vec3 &other) const { return (x * other.x + y * other.y + z * other.z); }

Vec3 Vec3::cross(const Vec3& other) const
{ return { y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x }; }

// Operations

Vec3 Vec3::operator* (const Vec3& rhs) const
{ return { x * rhs.x, y * rhs.y, z * rhs.z }; }

Vec3 Vec3::operator* (double scalar) const
{ return { x * scalar, y * scalar, z * scalar }; }

Vec3 Vec3::operator/ (const Vec3& rhs) const
{ return { x / rhs.x, y / rhs.y, z / rhs.z }; }

Vec3 Vec3::operator/ (double scalar) const
{ return { x / scalar, y / scalar, z / scalar }; }

Vec3 Vec3::operator+ (const Vec3& rhs) const
{ return { x + rhs.x , y + rhs.y, z + rhs.z };  }

Vec3 Vec3::operator+ (double scalar) const
{ return { x + scalar , y + scalar, z + scalar }; }

Vec3 Vec3::operator- (const Vec3& rhs) const
{ return { x - rhs.x , y - rhs.y, z - rhs.z }; }

Vec3 Vec3::operator- (double scalar) const
{ return { x - scalar , y - scalar, z - scalar }; }

Vec3 Vec3::operator- () const
{ return { -x , -y, -z }; }







