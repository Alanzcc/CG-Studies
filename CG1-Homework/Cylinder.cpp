#include "Cylinder.hpp"


Cylinder::Cylinder(double radius, double height, std::vector<double> ambientReflex, std::vector <double> diffuseReflex, std::vector <double> specularReflex, int specularExponent, std::vector<double> centerTop, std::vector<double> centerBottom) {
    this->radius = radius;
    this->height = height;
    this->ambientReflex = ambientReflex;
    this->diffuseReflex = diffuseReflex;
    this->specularReflex = specularReflex;
    this->specularExponent = specularExponent;
    this->centerTop = centerTop;
    this->centerBottom = centerBottom;
    this->axis = normalize(minusVectors(centerTop, centerBottom));
}


std::optional<std::vector<double>> Cylinder::doesItIntercept(Ray Ray) {
    
    //guardar os pontos de interseção válidos
    std::vector<std::vector<double>> validIntersections;
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
    
        double intersection1_projection = dotProduct(minusVectors(intersection1, centerBottom), axis);
        double intersection2_projection = dotProduct(minusVectors(intersection2, centerBottom), axis);

        if(intersection1_projection >= 0 && intersection1_projection <= height){
            validIntersections.push_back(intersection1);
        }

        if(intersection2_projection >= 0 && intersection2_projection <= height){
            validIntersections.push_back(intersection2);
        }

    //ver se interceptou o topo
    //ver se interceptou a base
    //guardar em valid Intersections
    //retornar o menor
   
    }
}

