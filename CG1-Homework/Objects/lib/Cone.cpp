#include "../include/cone.hpp"
#include <math.h>
//cone will need cone's vertex, axis, angle, height and radius
//if you have centerBase, you can calculate V = C + Hn 
// intersectionPoint a tint^2 + 2b tint + c = 0
//v is V - Po
// a = (d . n)^2 - (d.d) cos^2(angle)
// b = (v.d)cos^2(angle) - (v.n)(d.n)
// c = (v . n)^2 - (v.v)cos^2(angle)

//delta < 0 -> no intersection 
//delta = 0 -> one intersection
//delta > 0 -> two intersection

//Pint = Po + tint d

//if a is zero, ray is parallel to 'geratriz' 

// it's inside the cone if 0<= (V-P) . n <= H

//constructors

Cone::Cone(double angle, double height, Point vertex, Point center_bottom, Vec3 axis, double radius, Intensity emissive_color, Intensity ambient_color, Intensity diffuse_color, Intensity specular_color, double shininess)
    : angle(angle), height(height), vertex(vertex), axis(axis.normalize()), radius(radius), emissive_color(emissive_color), ambient_color(ambient_color), diffuse_color(diffuse_color), specular_color(specular_color), shininess(shininess), center_bottom(center_bottom), bottom(radius, center_bottom, -axis) {}

//intercept method for cone
std::optional<IntCol> Cone::intercept(const Ray &Ray) const {
    //v = V - Po
    Vec3 v = vertex - Ray.origin;
    //coefficient of the quadratic equation
    //d is direction?
    // a = (d . n)^2 - (d.d) cos^2(angle)
    // b = (v.d)cos^2(angle) - (v.n)(d.n)
    // c = (v . n)^2 - (v.v)cos^2(angle)

    //cos(angle) = tan(radius/height)
    double angle = atan(radius / height);
    double a = (std::pow(Ray.direction.dot(axis))) - (Ray.direction.dot(Ray.direction)) * std::pow(cos(angle));
    double b = 2 * (v.dot(Ray.direction)) * std::pow(cos(angle)) - (v.dot(axis)) * (Ray.direction.dot(axis));
    double c = (std::pow(v.dot(axis))) - (v.dot(v)) * std::pow(cos(angle));

    //delta = b^2 - 4ac
    double delta = std::pow(b, 2) - 4 * a * c;
    //if delta < 0 -> no intersection
    if (delta < 0) {
        return std::nullopt;
    }
    //if delta = 0 -> one intersection
    if (delta == 0) {
        double tint = -b / (2 * a);
        // it's inside the cone if 0<= (V-P) . n <= H
        Vec3 p1 = Ray.origin + tint * Ray.direction;
         //Pint = Po + tint d
        p1_projection = axis.dot(vertex - p1);
        if (p1_projection <= height) {
            return std::makepair(p1, get_emissive_color()); //checar
        }
        else {
            return std::nullopt;
        }
    }
    //two intersections 
    double tint1 = (-b + std::sqrt(delta)) / (2 * a);
    double tint2 = (-b - std::sqrt(delta)) / (2 * a);

    if (tint1 < 0 || tint2 < 0) {
        return std::nullopt;
    }

    //Point p1 = Ray.origin + tint1 * Ray.direction;
    //Point p2 = Ray.origin + tint2 * Ray.direction;

    // it's inside the cone if 0<= (V-P) . n <= H
    double p1_projection = axis.dot(vertex - p1);
    double p2_projection = axis.dot(vertex - p2);

    if(p1_projection > height || p1_projection < 0) {
        tint1 = -1;
    }

    if(p2_projection > height || p2_projection < 0) {
        tint2 = -1;
    }

    if(tint1 >= 0 && tint2 >= 0) {
        double minT = std::min(tint1, tint2);
        //std::makepair(Ray.origin + minT * Ray.direction, get_emissive_color());
    }

    //check if the bottom is intercepted
    bottom_inter = bottom->intercept(Ray);
    if (bottom_inter.has_value()) {
        //if the distance between the intersection point and the center of the base is greater than the radius, it's not valid
        if(bottom->first >= 0 && (Ray.origin + bottom->first * Ray.direction - center_bottom).norm() > radius) {
            if (bottom->first < minT) {
                return std::make_pair(bottom->first, get_emissive_color());
            } 
        }      
    }
    //return the closest intersection point
    return std::make_pair(Ray.origin + minT * Ray.direction, get_emissive_color());
}


//get_normal method for cone
std::optional<Vec3> Cone::get_normal(const Point &intersection) const {
    Vec3 normal;
    //vector from the vertex to the intersection point
    Vec3 vtp = intersection - vertex; //vp
    //vector from the center of the base to the intersection point
    Vec3 vcp = intersection - center_bottom;//v
    //dot product of vtp and axis 
    double vcp_dot_axis = vcp.dot(axis);
    //calculate normal
    //if it's less than err
    if (auto err = 1e-12; err < vcp_dot_axis) {
        normal = (vtp.cross(axis)).cross(vtp)
    } else {
        normal = -axis;
    }
return normal;
}

//getters 
Intensity Cone::get_emissive_color() const {
    return emissive_color;
}

Intensity Cone::get_ambient_color() const {
    return ambient_color;
}

Intensity Cone::get_diffuse_color() const {
    return diffuse_color;
}

Intensity Cone::get_specular_color() const {
    return specular_color;
}

double Cone::get_shininess() const {
    return shininess;
}
