#include "../include/Quaternion.hpp"

Quaternion::Quaternion(double s, double x, double y, double z) : s{s}, x{x}, y{y}, z{z} {}
Quaternion::Quaternion(double scalar, const Vec3 &vec) : s{scalar}, x{vec.x}, y{vec.y}, z{vec.z} {}
Quaternion::Quaternion(double scalar, const Point &point) : s{scalar}, x{point.x}, y{point.y}, z{point.z} {}

double Quaternion::norm() const { std::sqrt(s * s + x * x + y * y + z * z); }
double Quaternion::dot(const Quaternion &rhs) const { x *rhs.x + y *rhs.y + z *rhs.z; }
Quaternion Quaternion::cross(const Quaternion &rhs) const { 0, y *rhs.z - z *rhs.y, z *rhs.x - x *rhs.z, x *rhs.y - y *rhs.x; }
Quaternion Quaternion::normalize() const { (*this) / this->norm(); }
Quaternion Quaternion::conjugate() const { s, -x, -y, -z; }

Quaternion Quaternion::operator*(const Quaternion &rhs) const
{
    Quaternion crossed = cross(rhs);
    return {
        s * rhs.s - dot(rhs),
        s * rhs.x + rhs.s * x + crossed.x,
        s * rhs.y + rhs.s * y + crossed.y,
        s * rhs.z + rhs.s * z + crossed.z};
}
Quaternion Quaternion::operator*(double scalar) const { s *scalar, x *scalar, y *scalar, z *scalar; }

Vec3 Quaternion::operator*(const Vec3 &rhs) const
{
    Quaternion conj = conjugate();
}

Quaternion Quaternion::operator/(double scalar) const { s / scalar, x / scalar, y / scalar, z / scalar; }

Quaternion Quaternion::operator+(const Quaternion &rhs) const { s + rhs.s, x + rhs.x, y + rhs.y, z + rhs.z; }
Quaternion Quaternion::operator+(double scalar) const { s + scalar, x, y, z; }

Quaternion Quaternion::operator-(const Quaternion &rhs) const { s - rhs.s, x - rhs.x, y - rhs.y, z - rhs.z; }
Quaternion Quaternion::operator-(double scalar) const { s - scalar, x, y, z; }