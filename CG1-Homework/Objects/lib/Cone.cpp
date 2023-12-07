#include "../include/cone.hpp"

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

Cone::Cone(double angle, double height, Point vertex, Vec3 axis, double radius, Intensity emissive_color, Intensity ambient_color, Intensity diffuse_color, Intensity specular_color, double shininess)
    : angle(angle), height(height), vertex(vertex), axis(axis), radius(radius), emissive_color(emissive_color), ambient_color(ambient_color), diffuse_color(diffuse_color), specular_color(specular_color), shininess(shininess) {}