#include "vec3Math.hpp"

// Standard 3D vector operations

double dotProduct(std::vector<double> &vectorA, std::vector<double> &vectorB)
{
    double dot = (vectorA[0] * vectorB[0]) + (vectorA[1] * vectorB[1]) + (vectorA[2] * vectorB[2]);
    return dot;
}

std::vector<double> crossProduct(const std::vector<double> &vectorA, const std::vector<double> &vectorB)
{
    std::vector<double> vectorC;
    vectorC.push_back(vectorA[1] * vectorB[2] - vectorA[2] * vectorB[1]);
    vectorC.push_back(vectorA[2] * vectorB[0] - vectorA[0] * vectorB[2]);
    vectorC.push_back(vectorA[0] * vectorB[1] - vectorA[1] * vectorB[0]);
    return vectorC;
}

std::vector<double> normalize(const std::vector<double> &vector)
{
    double norm = sqrt(vector[0] * vector[0] + vector[1] * vector[1] + vector[2] * vector[2]);
    std::vector<double> normalized;
    if (norm != 0.0) {
        normalized.push_back(vector[0] / norm);
        normalized.push_back(vector[1] / norm);
        normalized.push_back(vector[2] / norm);
    }
    else {
        normalized.push_back(0.0);
        normalized.push_back(0.0);
        normalized.push_back(0.0);
    }
    return normalized;
}

// Operations bewteen vectors

std::vector<double> multiplyVectors(const std::vector<double> &vectorA, const std::vector<double> &vectorB)
{
    std::vector<double> multVector;
    multVector.push_back(vectorA[0] * vectorB[0]);
    multVector.push_back(vectorA[1] * vectorB[1]);
    multVector.push_back(vectorA[2] * vectorB[2]);
    return multVector;
}

std::vector<double> divideVectors(const std::vector<double> &vectorA, const std::vector<double> &vectorB)
{
    std::vector<double> vectorC = {vectorA[0] / vectorB[0], vectorA[1] / vectorB[1], vectorA[2] / vectorB[2]};
    return vectorC;
}

std::vector<double> plusVectors(const std::vector<double> &vectorA, const std::vector<double> &vectorB)
{
    std::vector<double> vectorC = {vectorA[0] + vectorB[0], vectorA[1] + vectorB[1], vectorA[2] + vectorB[2]};
    return vectorC;
}

std::vector<double> minusVectors(const std::vector<double> &vectorA, const std::vector<double> &vectorB)
{
    std::vector<double> vectorC = {vectorA[0] - vectorB[0], vectorA[1] - vectorB[1], vectorA[2] - vectorB[2]};
    return vectorC;
}

// Operations between vectors and scalars

std::vector<double> multiplyByScalar(const std::vector<double> &vector, double scalar)
{
    std::vector<double> scaledVector = {vector[0] * scalar, vector[1] * scalar, vector[2] * scalar};
    return scaledVector;
}

std::vector<double> divideByScalar(const std::vector<double> &vector, double scalar)
{
    std::vector<double> scaledVector = {vector[0] / scalar, vector[1] / scalar, vector[2] / scalar};
    return scaledVector;
}

std::vector<double> sumByScalar(const std::vector<double> &vector, double scalar)
{
    std::vector<double> scaledVector = {vector[0] + scalar, vector[1] + scalar, vector[2] + scalar};
    return scaledVector;
}

std::vector<double> subtractionByScalar(const std::vector<double> &vector, double scalar)
{
    std::vector<double> scaledVector = {vector[0] - scalar , vector[1] - scalar, vector[2] - scalar};
    return scaledVector;
}

