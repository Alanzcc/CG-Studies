#include "Point.hpp"

// Constructors
Point::Point() : x{ 0 }, y{ 0 }, z{ 0 } {}
Point::Point(const Vec3& vector) : x{ vector.x }, y{ vector.y }, z{ vector.z } {}
Point::Point(std::vector<double>& other) : x{ other[0] }, y{ other[1] }, z{ other[2] } {}
Point::Point(double a, double b, double c) : x{ a }, y{ b }, z{ c } {}

// Operations

Vec3 Point::operator*(const Point& rhs) const { return { x * rhs.x, y * rhs.y, z * rhs.z }; }
Vec3 Point::operator*(double scalar) const { return { x * scalar, y * scalar, z * scalar }; }

Vec3 Point::operator/(const Point& rhs) const { return { x / rhs.x, y / rhs.y, z / rhs.z }; }
Vec3 Point::operator/(double scalar) const { return { x / scalar, y / scalar, z / scalar }; }

Vec3 Point::operator+(const Point& rhs) const { return { x + rhs.x, y + rhs.y, z + rhs.z }; }
Vec3 Point::operator+(double scalar) const { return { x + scalar, y + scalar, z + scalar }; }

Vec3 Point::operator-(const Point& rhs) const { return { x - rhs.x, y - rhs.y, z - rhs.z }; }
Vec3 Point::operator-(double scalar) const { return { x - scalar, y - scalar, z - scalar }; }

Point::operator Vec3() const { return Vec3(x, y, z); }