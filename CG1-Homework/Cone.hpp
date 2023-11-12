#ifndef Cone_HPP
#define Cone_HPP
#include <vector>
#include <cmath>
#include <vector>
#include <optional> // pra que serve essa biblioteca?
#include <algorithm> // e essa tbm
#include "vec3Math.hpp" //dotProduct, crossProduct, normalize, multiplyVectors, divideVectors, plusVectors, minusVectors, multiplyByScalar, divideByScalar, sumByScalar, subtractionByScalar

class Cone
{
    public:
        Cone(double radius, //da base
            double height, //da altura
            std::vector<double> center, //do centro da base
            std::vector<double> ambientReflex, //reflexao ambiente
            std::vector<double> diffuseReflex, //reflexao difusa
            std::vector<double> specularReflex,//reflexao especular
            int specularExponent, //expoente especular
            double angle, //angulo da geratriz com o eixo do cone
            double coneVertex,//vertice do cone
            std::vector<double> coneDirection,//vetor unitario direcao e sentido do cone
            std::vector<double> anyPointInCone//ponto qualquer dentro do cone, eu deveria usar um doesItIntercept()?
            //ilumination here?
            );
};

#endif