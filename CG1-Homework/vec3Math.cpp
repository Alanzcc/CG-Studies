#include "vec3Math.hpp"

double dotProduct(double *vectorA, double *vectorB)
{
    double dot = (vectorA[0] * vectorB[0]) + (vectorA[1] * vectorB[1]) + (vectorA[2] * vectorB[2]);
    return dot;
}

double* crossProduct(double* vectorA, double* vectorB)
{
    double* vectorC  = (double*)malloc(sizeof(double) * 3);
    (vectorC)[0] = (vectorA[1] * vectorB[2] - vectorA[2] * vectorB[1]);
    (vectorC)[1] = (vectorA[2] * vectorB[0] - vectorA[0] * vectorB[2]);
    (vectorC)[2] = (vectorA[0] * vectorB[1] - vectorA[1] * vectorB[0]);
    return vectorC;
}

double* lightProduct(double* intensity, double* reflexivity)
{
double* lightingVector = (double*)malloc(sizeof(double) * 3);
lightingVector[0] = intensity[0] * reflexivity[0];
lightingVector[1] = intensity[1] * reflexivity[1];
lightingVector[2] = intensity[2] * reflexivity[2];
return lightingVector;
}

double* normalizer(double* vector)
{
    double norm = sqrt(vector[0] * vector[0] + vector[1] * vector[1] + vector[2] * vector[2]);
    if (norm != 0.0) {
        vector[0] = (vector[0] / norm);
        vector[1] = (vector[1] / norm);
        vector[2] = (vector[2] / norm);
    }
    else {
        vector[0] = 0.0;
        vector[1] = 0.0;
        vector[2] = 0.0;
    }
    return vector;
}
