#ifndef vec3Math_HPP
#define vec3Math_HPP

#include <cmath>

double dotProduct(double *vectorA, double *vectorB);
double *crossProduct(double *vectorA, double *vectorB);
double *lightProduct(double *intensity, double *reflexivity);
double *normalizer(double *vector);

#endif