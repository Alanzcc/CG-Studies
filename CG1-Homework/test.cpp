#include "vec3Math.hpp"
#include <iostream>
#include <cmath>
#include <algorithm>
#include <optional>
#include <utility>


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


class Ray
{
public:
    // 3d point and 3d normalized vector
    double *initialPoint;
    double *direction;
    double *lightSourceIntensity;

    Ray(double *initialPoint, double *direction, double *lightSourceIntensity)
    {
        this->initialPoint = initialPoint;
        this->direction = normalizer(direction);
        this->lightSourceIntensity = lightSourceIntensity;
    };
};

class Sphere
{
public:
    double radius;

    // 3d point
    double *center, *reflexivity;

    Sphere(double radius, double *center, double *reflexivity)
    {
        this->radius = radius;
        this->center = center;
        this->reflexivity = reflexivity;
    }

    std::pair<double *, double *> doesItIntercept(Ray Ray)
    {
        // w is a vector
        double w[3] = {(Ray.initialPoint[0] - this->center[0]), (Ray.initialPoint[1] - this->center[1]),
                       (Ray.initialPoint[2] - this->center[2])};

        double bi = dotProduct(w, Ray.direction);
        double dotW = dotProduct(w, w);
        double c = dotW - (this->radius * this->radius);
        double delta = std::pow(bi, 2) - 4 * c;

        if (delta >= 0)
        {
            double *lightingVector = lightProduct(Ray.lightSourceIntensity, reflexivity);

            double intersectionScalar = std::min((-bi + std::sqrt(delta)) / 2, (-bi - std::sqrt(delta)) / 2);

            double intersectionPoint[3] = {(Ray.initialPoint[0] - Ray.direction[0] * intersectionScalar),
                                           (Ray.initialPoint[1] - Ray.direction[1] * intersectionScalar),
                                           (Ray.initialPoint[2] - Ray.direction[2] * intersectionScalar)};

            double normalVector[3] = {(intersectionPoint[0] - center[0]) / radius,
                                      (intersectionPoint[1] - center[1]) / radius,
                                      (intersectionPoint[2] - center[2]) / radius};

            double lVector[3] = {-(intersectionPoint[0] - Ray.initialPoint[0]),
                                 -(intersectionPoint[1] - Ray.initialPoint[1]),
                                 -(intersectionPoint[2] - Ray.initialPoint[2])};
            double *lightVector = normalizer(lVector);

            double reflectedLightVector[3] = {2 * dotProduct(normalVector, lightVector) * normalVector[0] - lightVector[0],
                                              2 * dotProduct(normalVector, lightVector) * normalVector[1] - lightVector[1],
                                              2 * dotProduct(normalVector, lightVector) * normalVector[2] - lightVector[2]};

            double diffusionFactor = dotProduct(lightVector, normalVector);
            double iluminationDiffusion[3] = {lightingVector[0] * diffusionFactor,
                                              lightingVector[1] * diffusionFactor,
                                              lightingVector[2] * diffusionFactor};

            double specularityFactor = pow(dotProduct(reflectedLightVector, lightVector), 5); // This 5 is a placeholder for the m variable
            double iluminationSpecular[3] = {lightingVector[0] * specularityFactor,
                                             lightingVector[1] * specularityFactor,
                                             lightingVector[2] * specularityFactor};

            double ilumination[3] = {iluminationDiffusion[0] + iluminationSpecular[0],
                                     iluminationDiffusion[1] + iluminationSpecular[1],
                                     iluminationDiffusion[2] + iluminationSpecular[2]};
            return std::make_pair(intersectionPoint, ilumination);
        }
        double didntIntercept[3] = {0, 0, 0};
        double backgroundColor[3] = {100, 100, 100};
        return std::make_pair(didntIntercept, backgroundColor);
    }
};

class Canvas
{
public:
    int windowWidth, windowHeight, windowDistance, numLines,
        numColumns, deltaX, deltaY, windowMinX, windowMaxY;

    Canvas(int windowWidth, int windowHeight, int windowDistance, int numLines, int numColumns)
    {
        this->windowWidth = windowWidth;
        this->windowHeight = windowHeight;
        this->windowDistance = windowDistance;
        this->numLines = numLines;
        this->numColumns = numColumns;
        this->deltaX = windowWidth / numColumns;
        this->deltaY = windowHeight / numLines;
        this->windowMinX = -(windowWidth / 2);
        this->windowMaxY = windowHeight / 2;
    }

    std::pair<double *, double *> **Raycast(double *lightSourcePos, double *lightSourceIntensity, Sphere Sphere)
    {
        int xC, yL;
        std::pair<double *, double *> intercepted;

        std::pair<double *, double *> **canvas = new std::pair<double *, double *> *[this->numLines];
        for (int line = 0; line < this->numLines; line++)
        {
            yL = windowMaxY - (deltaY / 2) - (line * deltaY);
            for (int column = 0; column < numColumns; column++)
            {
                xC = windowMinX + (deltaX / 2) + (column * deltaX);
                double windowPoint[3] = {(double)xC, (double)yL, (double)-windowDistance};
                Ray Ray(lightSourcePos, windowPoint, lightSourceIntensity);
                intercepted = Sphere.doesItIntercept(Ray);
                canvas[line][column] = intercepted;
            }
        }
    return canvas;
    }
};
int main()
{
    int windowDistance = 300;
    double lightSourcePos[3] = {0, 5, 0};
    double lightSourceIntensity[3] = {0.7, 0.7, 0.7};
    double windowPoint[3] = {1, 1, (double)-windowDistance};
    Ray Ray(lightSourcePos, windowPoint, lightSourceIntensity);

    double radius = 400;
    double center[3] = {0, 0, -(windowDistance + radius)};
    double reflexivity[3] = {0.5, 0.5, 0.5};
    Sphere Sphere(radius, center, reflexivity);
    std::pair<double *, double *> a = Sphere.doesItIntercept(Ray);
    double *b;
    b = a.second;
    printf("%f\n", b[2]);
    return 0;
}