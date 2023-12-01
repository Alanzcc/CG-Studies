/* #include "Cylinder.hpp"


Cylinder::Cylinder(double radius, double height, std::vector<double> ambientReflex, std::vector <double> diffuseReflex, std::vector <double> specularReflex, int specularExponent, std::vector<double> centerTop, std::vector<double> centerBottom, int shininess) {
    this->radius = radius;
    this->height = height;
    this->ambientReflex = ambientReflex;
    this->diffuseReflex = diffuseReflex;
    this->specularReflex = specularReflex;
    this->specularExponent = specularExponent;
    this->centerTop = centerTop;
    this->centerBottom = centerBottom;
    this->axis = normalize(minusVectors(centerTop, centerBottom));
    this->shininess = shininess;
}


std::optional<std::vector<double>> Cylinder::doesItIntercept(Ray Ray) {
    
    //guardar os pontos de interseção válidos
    //std::vector<std::vector<double>> validIntersections;
    //calcular v e w 
    // v = (Po - B) - ((Po - B) . u)u
    std::vector<double> v = minusVectors(minusVectors(Ray.initialPoint, centerBottom), multiplyByScalar(axis, dotProduct(minusVectors(Ray.initialPoint, centerBottom), axis)));
    // w = d - (d. u)u
    std::vector<double> w = minusVectors(Ray.direction, multiplyByScalar(axis, dotProduct(Ray.direction, axis)));
    
    //coeficientes da equação quadrática
    double a = dotProduct(w, w);
    double b = 2 * dotProduct(v, w);
    double c = dotProduct(v, v) - (radius * radius);
    double delta = (b * b) - (4.0 * a * c);
    if (delta < 0.0) {
        return std::nullopt; //sem interseção
    }
    if (a != 0 && delta >= 0)
    {
        //parâmetros da interseção
        double t1 = (-b + sqrt(delta)) / (2.0 * a);
        double t2 = (-b - sqrt(delta)) / (2.0 * a);

        //calcular os pontos de interseção
        std::vector<double> intersection1 = plusVectors(Ray.initialPoint, multiplyByScalar(Ray.direction, t1));
        std::vector<double> intersection2 = plusVectors(Ray.initialPoint, multiplyByScalar(Ray.direction, t2));

        //verificar se a interseção está dentro do cilindro 
        // 0 <= (P - B) . u <= height
        double minT = std::numeric_limits<double>::infinity();
        std::vector<double> closestInterception;
        double intersection1_projection = dotProduct(minusVectors(intersection1, centerBottom), axis);
        double intersection2_projection = dotProduct(minusVectors(intersection2, centerBottom), axis);

        if(intersection1_projection >= 0 && intersection1_projection <= height){
            if (t1 < minT) {
                minT = t1;
                closestInterception = intersection1;
            }
            closestInterception = intersection1;
        }

        if(intersection2_projection >= 0 && intersection2_projection <= height){
            if(t2 < minT){
                minT = t2;
                closestInterception = intersection2;
            }
        }

    //ver se interceptou o topo
    //ver se interceptou a base e ir atualizando minT se t for menor 

    //verificar se há interseções válidas
    //se minT ainda é igual a infinito, não há interseção
    if (minT == std::numeric_limits<double>::infinity()){
        return std::nullopt;    
    }

    return closestInterception;
}
}

std::vector<double> Cylinder::Illumination(Ray Ray, std::vector<double> intensity)
{
    std::vector<double> illumination;
    std::vector<double> interPoint = doesItIntercept(Ray).value_or(std::vector<double>(3, -2));
    if (interPoint[0] != -2)
    {
        std::vector<double> light = normalize(minusVectors(Ray.initialPoint, interPoint));

        std::vector<double> normal = normalize(divideByScalar(axis, this->radius));

    std::vector<double> reflected = minusVectors(multiplyByScalar(normal, 2 * dotProduct(light, normal)), light);

        std::vector<double> vision = multiplyByScalar(normalize(minusVectors(interPoint, Ray.initialPoint)), -1); // While cam = ray_source

        double diffusionFactor = dotProduct(light, normal);
        double specularFactor = pow(dotProduct(reflected, vision), this->shininess);

        std::vector<double> ambientIllumination = multiplyVectors(intensity, this->ambientReflex);
        std::vector<double> diffusionIllumination = multiplyByScalar(multiplyVectors(intensity, this->diffuseReflex), diffusionFactor);
        std::vector<double> specularIllumination = multiplyByScalar(multiplyVectors(intensity, this->specularReflex), specularFactor);

        illumination = plusVectors(ambientIllumination, plusVectors(diffusionIllumination, specularIllumination));
    }
    else
    {
        illumination.resize(3, -2);
    }

    return illumination;
}
*/

#include "Cylinder.hpp"

//constructor for cylinder

Cylinder::Cylinder(Vec3 direction, double radius, double height, Point centerBottom, Point centerTop, Vec3 axis, CircularPlane* bottom, CircularPlane* top, Intensity emissive_color, Intensity ambient_color, Intensity diffuse_color, Intensity specular_color, double shininess)
    : direction(direction), radius(radius), height((centerBase - centerTop).norm()), centerBase(centerBase), centerTop(centerTop), axis(normalize(centerBase - centerTop)), bottom(bottom), top(top), emissive_color(emissive_color), ambient_color(ambient_color), diffuse_color(diffuse_color), specular_color(specular_color),
    shininess(shininess) {
        Vec3 bottomNormal = -axis;
        bottom = new CircularPlane(radius, centerBottom, bottomNormal)

        Vec3 topNormal = axis;
        top = new CircularPlane(radius, centerTop, topNormal)
    }

//intercept method for cylinder

std::optional<IntCol> Cylinder::doesItIntercept(Ray Ray) {
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

    else{
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
            if (p1_projection >= 0 && p1_projection <= height) {
                validPoints.push_back(std::make_pair(t1, p1));
            }
        }
        if(t2>=0) {
            if (p2_projection >= 0 && p2_projection <= height) {
                validPoints.push_back(std::make_pair(t2, p2));
            }}
        
        //then we check if the ray intercepts the top and bottom planes

    std::optional<IntCol> bottom = bottom->doesItIntercept(Ray);
    std::optional<IntCol> top = top->doesItIntercept(Ray);


}
}

