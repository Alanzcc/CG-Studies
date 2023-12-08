#include "../include/Cylinder.hpp"

Cylinder::Cylinder(double radius, double height, Point center_bottom, Vec3 axis,
                    Intensity emissive_color, Intensity ambient_color, Intensity diffuse_color,
                    Intensity specular_color, double shininess) : radius(radius), height(height),
                    center_bottom(center_bottom), axis(axis.normalize()), emissive_color(emissive_color),
                    ambient_color(ambient_color), diffuse_color(diffuse_color), specular_color(specular_color), shininess(shininess),
                    bottom(radius, center_bottom, -axis), top(radius, center_bottom + (axis * height), axis) {} 

Cylinder::Cylinder(double radius, double height, Point center_bottom, Vec3 axis) : radius(radius), height(height),
                    center_bottom(center_bottom), axis(axis.normalize()), emissive_color(1, 1, 1),
                    ambient_color(1, 1, 1), diffuse_color(1, 1, 1), specular_color(1, 1, 1), shininess(1),
                    bottom(radius, center_bottom, -axis), top(radius, center_bottom + (axis * height), axis) {} 

//intercept method for cylinder
std::optional<IntCol> Cylinder::intercept(const Ray &Ray) const {
    //v, w
    // v = (Po - B) - ((Po - B) . u)u
    Vec3 v = (Ray.origin - centerBottom) - (axis *(axis.dot(Ray.origin - centerBottom)));
    // w = d - (d. u)u
    Vec3 w = (Ray.direction) - axis * (Ray.direction.dot(axis));

    //coefficient of the quadratic equation
    double a = w.dot(w);
    double b = 2 * v.dot(w);
    double c = v.dot(v) - (radius * radius);
    double delta = (b * b) - (4.0 * a * c);

    if delta < 0 {
        return std::nullopt; //no intersection
    }

    //parameters of the intersection
    double t1 = (-b + sqrt(delta)) / (2.0 * a);
    double t2 = (-b - sqrt(delta)) / (2.0 * a);
    //p1
    Vec3 p1 = Ray.origin + Ray.direction * t1;
    //p2
    Vec3 p2 = Ray.origin + Ray.direction * t2;

    //create a vector that will store the valid points so we choose the closest one
    std::vector<std::pair<double, Point>> validPoints;

    //0 ≤ (P - B) . u ≤ height; so we know if p1 and p2 are in the cylinder (validPoints)
    double p1_projection = axis.dot(p1 - centerBottom);
    double p2_projection = axis.dot(p2 - centerBottom);

    if(t1>=0) {
        if (p1_projection >= 0 && p1_projection <= height)
            validPoints.push_back(std::make_pair(t1, p1));
    }
    if(t2>=0) {
        if (p2_projection >= 0 && p2_projection <= height)
            validPoints.push_back(std::make_pair(t2, p2));
    }
            
            //then we check if the ray intercepts the bottom and top planes

    std::optional<IntCol> bottom_inter = bottom->intercept(Ray);
    std::optional<IntCol> top_inter = top->intercept(Ray);

    if (bottom_inter.has_value() && top_inter.has_value()) {
        //length of the ray from the origin to the intersection point of the bottom plane
        double inter_length_rayB = (bottom_inter->first - Ray.origin).norm();
        // ''' top plane
        double inter_length_rayT = (top_inter->first - Ray.origin).norm();

        //if the ray intersects the bottom plane first
        if (inter_length_rayB < inter_length_rayT)
            //if the intersection point is inside the cylinder
            validPoints.push_back(std::make_pair(inter_length_rayB, bottom->first));
        else
            validPoints.push_back(std::make_pair(inter_length_rayT, top->first));
    }
    else if (bottom.has_value())
        validPoints.push_back(std::make_pair((bottom->first - Ray.origin).norm(), bottom->first));
    
    else if (top.has_value())
        validPoints.push_back(std::make_pair((top->first - Ray.origin).norm(), top->first));

    //find the minimum t (the closest point)
    double minT = std::numeric_limits<double>::infinity();
    Point closestPoint = Ray.origin;

    //(t, p)
    for (auto& point : validPoints) {
        if (point.first < minT) {
            minT = point.first; 
            closestPoint = point.second;
        }
    }

    //if there is no intersection
    if (minT == std::numeric_limits<double>::infinity())
        return std::nullopt;
    else
        return std::make_pair(closestPoint, get_emissive_color());
    
}  


//General Case:
//If the given point is not on either base, the code calculates the normal vector by finding the point (pt) on the axis of the cylinder that is closest to the given point (p). The normal vector is then the normalized vector from p to pt. It is rotation-sensitive.

if ((p - top_base).length() < radius) {
    normal = dir;
  } else if ((p - base_center).length() < radius) {
    normal = dir * -1;

//normal method for cylinder
std::optional<Vec3> Cylinder::get_normal(const Vec3 &intersection) const {
    Vec3 normal; 
    Point center_top = center_bottom + (axis * height);
    //if the intersection is on the top plane
    if ((intersection - center_top).norm() < radius) {
        normal = axis
    }
    //if the intersection is on the bottom plane
    else if ((intersection - center_bottom).norm() < radius) {
        normal = axis * -1;
    }
    //if the intersection is on the cylinder
    else {
        //pt
        Vec3 pt = centerBottom + axis * (axis.dot(intersection - centerBottom));
        //normal vector
        Vec3 normal = (intersection - pt).normalize();   
    }
    return normal;
}

//getters
Intensity Cylinder::get_emissive_color() const {
    return emissive_color;
}

Intensity Cylinder::get_ambient_color() const {
    return ambient_color;
}

Intensity Cylinder::get_diffuse_color() const {
    return diffuse_color;
}

Intensity Cylinder::get_specular_color() const {
    return specular_color;
}

double Cylinder::get_shininess() const {
    return shininess;
}

