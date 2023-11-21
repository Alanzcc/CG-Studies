/* #include "Cylinder.hpp"


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


std::optional<std::vector<double>> Cylinder::doesItIntercept(Ray Ray){
    
    //calcular v e w 
    // v = (Po - B) - ((Po - B) . u)u
    std::vector<double> v = minusVectors(minusVectors(Ray.initialPoint, centerBottom), multiplyByScalar(axis, dotProduct(minusVectors(Ray.initialPoint, centerBottom), axis)));
    // w = d - (d. u)u
    std::vector<double> w = minusVectors(Ray.direction, multiplyByScalar(axis, dotProduct(Ray.direction, axis)));
    
    //coeficientes da equação quadrática
    double a = dotProduct(w, w);
    if (a == 0.0) {
        return std::nullopt; //raio paralelo à superfície do cilindro
    }

    double b = 2 * dotProduct(v, w);
    double c = dotProduct(v, v) - (radius * radius);
    double delta = (b * b) - (4.0 * a * c);
    if (delta < 0.0) {
        return std::nullopt; //sem interseção
    }
    //parâmetros da interseção
    double t1 = (-b + sqrt(delta)) / (2.0 * a);
    double t2 = (-b - sqrt(delta)) / (2.0 * a);

    //calcular os pontos de interseção
    std::vector<double> intersection1 = plusVectors(Ray.initialPoint, multiplyByScalar(Ray.direction, t1));
    std::vector<double> intersection2 = plusVectors(Ray.initialPoint, multiplyByScalar(Ray.direction, t2));

    //verificar se a interseção está dentro do cilindro 
    // 0 <= (P - B) . u <= height
    
    double height_u1 = dotProduct(minusVectors(intersection1, centerBottom), axis);
    double height_u2 = dotProduct(minusVectors(intersection2, centerBottom), axis);

     if ((height_u1 >= 0.0 && height_u1 <= height) || (height_u2 >= 0.0 && height_u2 <= height)) {
        return (height_u1 >= 0.0 && height_u1 <= height) ? intersection1 : intersection2;  // Retorna o ponto de interseção válido
    }
    return std::nullopt; //sem interseção válida

}
*/