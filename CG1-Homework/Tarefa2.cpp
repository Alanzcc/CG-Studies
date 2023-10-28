#include <iostream>
#include <cmath>
#include <algorithm>
#include <utility>


#define SDL_MAIN_HANDLED
#include "SDL.h"

// Tarefa 1:
// intersectionPoint = initialPoint + direction * tInt
// ||intersectionPoint - center||^2 = radius^2
// ||initialPoint + direction * tInt - center||^2 = radius^2
//   w~ = initialPoint - center
//  (w~ + direction * tInt) . (w~ + direction * tInt) - radius^2 = 0
//  (w~ . w~) + tInt(w~ . direction) + tInt(direction . w~) tInt^2(direction . direction) - radius^2 = 0
//   a * tInt^2 + b * tInt + c = 0
//  (direction . direction)tInt^2 + tInt(2(w~ . direction)) + (w~ . w~) - radius^2 = 0

// example vector r . vector r = 1
// a = direction . direction = 1

// bi = w~ . direction
// b = 2 * (w~ . direction)
// b = 2 * bi

// c = (w~ . w~) - radius^2

// tInt = (-bi +- sqrt(delta)) / 2a
// delta = bi^2 - 4c
// if delta >= 0 the ray intercepts the sphere

// Tarefa 2: O raio de luz ainda sai do observador então initialPoint e observer são iguais
// Vetores importantes: 'v' vetor de visão, 'n' vetor normal, 'r' vetor de reflexão, 'l' vetor de luz

// Vetor normal na esfera:
// n = (intersectionPoint - center) / radius
// n = (initialPoint + direction * tInt - center) / radius
// n = (w~ + direction * tInt) / radius

// v =  -(intersectionPoint - observer) / ||intersectionPoint - observer||
/*
        // v =  -(intersectionPoint - observer) / ||intersectionPoint - observer||
        double visionVector[3] = {intersectionPoint[0] - observer[0],
                                              intersectionPoint[1] - observer[1],
                                              intersectionPoint[2] - observer[2]};

    */

    // l = (initialPoint - intersectionPoint) / ||initialPoint - intersectionPoint||
    // r = 2(n . l)n - l

    // I = I_a + I_d + I_e

    // I_a = (I_F@K) // No caso da tarefa 2, a iluminação ambiente é nula

    // fD é o 'Fator de difusão'
    // fD = (l . n)
    // I_d =( I_F@K) * fD

    // fE é o 'Fator de especularidade'
    // fE = (r . v)^m
    // I_e = (I_F@K) * fE

    // I_F = (0.7, 0.7, 0.7)  Intensidade da fonte pontual
    // P_F = (0, 5, 0)  Posição da fonte pontual situada a 5 metros acima do olho do observador.

    // K = (0.5, 0.5, 0.5)  Coeficiente de reflexão da superfície da esfera

    // Light = I@K


double dotProduct(double* vectorA, double* vectorB)
{
    double dot = (vectorA[0] * vectorB[0]) + (vectorA[1] * vectorB[1]) + (vectorA[2] * vectorB[2]);
    return dot;
}

double* crossProduct(double* vectorA, double* vectorB)
{
    double* vectorC = (double*)malloc(sizeof(double) * 3);
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
    double* initialPoint;
    double* direction;
    double* lightSourceIntensity;

    Ray(double* initialPoint, double* direction, double* lightSourceIntensity)
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
    double* center, * reflexivity;

    Sphere(double radius, double* center, double* reflexivity)
    {
        this->radius = radius;
        this->center = center;
        this->reflexivity = reflexivity;
    }

    std::pair<double*, double*> doesItIntercept(Ray Ray)
    {
        // w is a vector
        double w[3] = { (Ray.initialPoint[0] - this->center[0]), (Ray.initialPoint[1] - this->center[1]),
                       (Ray.initialPoint[2] - this->center[2]) };

        double bi = dotProduct(w, Ray.direction);
        double dotW = dotProduct(w, w);
        double c = dotW - (this->radius * this->radius);
        double delta = std::pow(bi, 2) - 4 * c;

        if (delta >= 0)
        {
            double* lightingVector = lightProduct(Ray.lightSourceIntensity, reflexivity);

            double intersectionScalar = std::min((-bi + std::sqrt(delta)) / 2, (-bi - std::sqrt(delta)) / 2);

            double intersectionPoint[3] = { (Ray.initialPoint[0] - Ray.direction[0] * intersectionScalar),
                                           (Ray.initialPoint[1] - Ray.direction[1] * intersectionScalar),
                                           (Ray.initialPoint[2] - Ray.direction[2] * intersectionScalar) };

            double normalVector[3] = { (intersectionPoint[0] - center[0]) / radius,
                                      (intersectionPoint[1] - center[1]) / radius,
                                      (intersectionPoint[2] - center[2]) / radius };

            double lVector[3] = { -(intersectionPoint[0] - Ray.initialPoint[0]),
                                 -(intersectionPoint[1] - Ray.initialPoint[1]),
                                 -(intersectionPoint[2] - Ray.initialPoint[2]) };
            double* lightVector = normalizer(lVector);

            double reflectedLightVector[3] = { 2 * dotProduct(normalVector, lightVector) * normalVector[0] - lightVector[0],
                                              2 * dotProduct(normalVector, lightVector) * normalVector[1] - lightVector[1],
                                              2 * dotProduct(normalVector, lightVector) * normalVector[2] - lightVector[2] };
                
            double diffusionFactor = dotProduct(lightVector, normalVector);
            double iluminationDiffusion[3] = { lightingVector[0] * diffusionFactor,
                                              lightingVector[1] * diffusionFactor,
                                              lightingVector[2] * diffusionFactor };

            double specularityFactor = pow(dotProduct(reflectedLightVector, lightVector), 5); // This 5 is a placeholder for the m variable
            double iluminationSpecular[3] = { lightingVector[0] * specularityFactor,
                                             lightingVector[1] * specularityFactor,
                                             lightingVector[2] * specularityFactor };

            double ilumination[3] = { iluminationDiffusion[0] + iluminationSpecular[0],
                                     iluminationDiffusion[1] + iluminationSpecular[1],
                                     iluminationDiffusion[2] + iluminationSpecular[2] };
            return std::make_pair(intersectionPoint, ilumination);
        }
        double didntIntercept[3] = { 0, 0, 0 };
        double backgroundColor[3] = { 100, 100, 100 };
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

    std::pair<double*, double*>** Raycast(double* lightSourcePos, double* lightSourceIntensity, Sphere Sphere)
    {
        int xC, yL;
        std::pair<double*, double*>intercepted;

        std::pair<double*, double*>** canvas = new std::pair<double*, double*> * [this->numLines];
        for (int line = 0; line < this->numLines; line++)
        {
            yL = windowMaxY - (deltaY / 2) - (line * deltaY);
            for (int column = 0; column < numColumns; column++)
            {
                xC = windowMinX + (deltaX / 2) + (column * deltaX);
                double windowPoint[3] = { (double)xC, (double)yL, (double)-windowDistance };
                Ray Ray(lightSourcePos, windowPoint, lightSourceIntensity);
                intercepted = Sphere.doesItIntercept(Ray);
                canvas[line][column] = intercepted;
            }
        }
        return canvas;
    }


};

// The observer is at the lightSourcePos(0, 0, 0)
// The Sphere's center must be at z < -(windowDistance + radius)
// gl_CLEAR_COLOR(100, 100, 100)

//

// P_F = (0, 5, 0)  Posição da fonte pontual situada a 5 metros acima do olho do observador.
int main()
{

    double lightSourcePos[3] = { 0, 5, 0 };
    double lightSourceIntensity[3] = { 0.7, 0.7, 0.7 };
    int windowDistance = 300;
    int windowWidth = 1280;
    int windowHeight = 720;
    int numColumns = 1280;
    int numLines = 720;

    // Inicialização  da tela

    SDL_SetMainReady();
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        SDL_Log("Não foi possível inicializar o SDL");
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow(
        "Esfera",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        windowWidth,
        windowHeight,
        SDL_WINDOW_SHOWN);

    if (!window)
    {
        SDL_Log("Não foi possível criar a janela");
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer)
    {
        SDL_Log("Não foi possível criar o renderer");
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    // ---------------------------------------------------------------

    // Inicialização da canvas, esfera, display e variáveis auxiliares
    Canvas canvas(windowWidth, windowHeight, windowDistance, numLines, numColumns);

    double radius = 400;
    double center[3] = { 0, 0, -(windowDistance + radius) };
    double reflexivity[3] = { 0.5, 0.5, 0.5 };
    Sphere sphere(radius, center, reflexivity);

    std::pair<double*, double*>** display = canvas.Raycast(lightSourcePos, lightSourceIntensity, sphere);

    bool isRunning = true;
    SDL_Event event;
    // ---------------------------------------------------------------

    while (isRunning)
    {

        // Processa eventos
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                isRunning = false;
            }
        }
        // -----------------------------

        SDL_RenderClear(renderer);

        // Desenha a tela
        for (int i = 0; i < numLines; i++)
        {
            for (int j = 0; j < numColumns; j++)
            {
                double* d = display[j][i].second;
                SDL_SetRenderDrawColor(renderer, d[0], d[1], d[2], 255);
                SDL_RenderDrawPoint(renderer, j, i);
            }
        }

        SDL_RenderPresent(renderer);
    }
    // Desaloca a memória e encerra o programa
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}