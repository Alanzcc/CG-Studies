#include "Point.hpp"

// Constructors
Point::Point() : x{0}, y{0}, z{0} {}
Point::Point(const Vector& vector) : x{vector.x}, y{vector.y}, z{vector.z} {}
Point::Point(std::vector<double>& other) : x{other[0]}, y{other[1]}, z{other[2]} {}
Point::Point(double a, double b, double c) : x{a}, y{b}, z{c} {}

// Operations

Vector Point::operator*(const Point& rhs) const { return { x * rhs.x, y * rhs.y, z * rhs.z }; }
Vector Point::operator*(double scalar) const { return { x * scalar, y * scalar, z * scalar }; }

Vector Point::operator/ (const Point& rhs) const { return { x / rhs.x, y / rhs.y, z / rhs.z }; }
Vector Point::operator/ (double scalar) const { return { x / scalar, y / scalar, z / scalar }; }

Vector Point::operator+ (const Point& rhs) const { return { x + rhs.x , y + rhs.y, z + rhs.z }; }
Vector Point::operator+(double scalar) const { return { x + scalar , y + scalar, z + scalar }; }

Vector Point::operator- (const Point& rhs) const { return { x - rhs.x , y - rhs.y, z - rhs.z }; }
Vector Point::operator-(double scalar) const { return { x - scalar , y - scalar, z - scalar }; }

Point::operator Vector() const { return Vector(x, y, z); }