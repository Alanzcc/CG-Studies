#ifndef vec3Math_HPP
#define vec3Math_HPP
#include <vector>
#include <cmath>

// Standard 3D vector operations
double dotProduct(std::vector<double> &vectorA, std::vector<double> &vectorB);
std::vector<double> crossProduct(const std::vector<double> &vectorA, const std::vector<double> &vectorB);
std::vector<double> normalize(const std::vector<double> &vector);

// Operations bewteen vectors
std::vector<double> multiplyVectors(const std::vector<double> &vectorA, const std::vector<double> &vectorB);
std::vector<double> divideVectors(const std::vector<double> &vectorA, const std::vector<double> &vectorB);
std::vector<double> plusVectors(const std::vector<double> &vectorA, const std::vector<double> &vectorB);
std::vector<double> minusVectors(const std::vector<double> &vectorA, const std::vector<double> &vectorB);

// Operations between vectors and scalars
std::vector<double> multiplyByScalar(const std::vector<double> &vector, double scalar);
std::vector<double> divideByScalar(const std::vector<double> &vector, double scalar);
std::vector<double> sumByScalar(const std::vector<double> &vector, double scalar);
std::vector<double> subtractionByScalar(const std::vector<double> &vector, double scalar);



#endif