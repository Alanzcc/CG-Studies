#include <iostream>
#include <cmath>
#define SDL_MAIN_HANDLED
#include "SDL.h"


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

// tInt = -bi +- sqrt(delta)
// delta = bi^2 - c
// if delta >= 0 the ray intercepts the sphere

double dotProduct(double* vectorA, double* vectorB)
{
    double dot = (vectorA[0] * vectorB[0]) + (vectorA[1] * vectorB[1]) + (vectorA[2] * vectorB[2]);
    return dot;
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

    Ray(double* initialPoint, double* direction)
    {
        this->initialPoint = initialPoint;
        this->direction = normalizer(direction);
    };
};

class Sphere
{
public:
    double radius;
    // 3d point
    double* center;

    Sphere(double radius, double* center)
    {
        this->radius = radius;
        this->center = center;
    }

    bool doesItIntercept(Ray Ray)
    {
        // w is a vector
        double w[3] = { (Ray.initialPoint[0] - this->center[0]), (Ray.initialPoint[1] - this->center[1]),
                       (Ray.initialPoint[2] - this->center[2]) };

        double bi = dotProduct(w, Ray.direction);

        double dotW = dotProduct(w, w);
        double c = dotW - (this->radius * this->radius);

        return (bi * bi - c >= 0);
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

    int** Raycast(double* observer, Sphere Sphere)
    {
        int xC, yL, intercepted;

        int** canvas = new int* [this->numLines];
        for (int i = 0; i < this->numLines; i++)
        {
            canvas[i] = new int[this->numColumns];
            for (int j = 0; j < this->numColumns; j++)
            {
                canvas[i][j] = 0;
            }
        }

        for (int l = 0; l < this->numLines; l++)
        {
            yL = windowMaxY - (deltaY / 2) - (l * deltaY);
            for (int c = 0; c < numColumns; c++)
            {
                xC = windowMinX + (deltaX / 2) + (c * deltaX);
                double windowPoint[3] = { (double)xC, (double)yL, (double)-windowDistance };
                Ray Ray(observer, windowPoint);
                intercepted = Sphere.doesItIntercept(Ray);
                if (intercepted)
                {
                    canvas[l][c] = 1;
                }
            }
        }

        return canvas;
    }
};

// The observer is at the origin(0, 0, 0)
// The Sphere's center must be at z < -(windowDistance + radius)
// gl_CLEAR_COLOR(100, 100, 100)

//


int main()
{


    double origin[3] = { 0, 0, 0 };
    int windowDistance = 300;
    int windowWidth = 1280;
    int windowHeight = 720;
    int numColumns = 1280;
    int numLines = 720;

  
    SDL_SetMainReady();
    if (SDL_Init(SDL_INIT_VIDEO) < 0) { 
        SDL_Log("Não foi possível inicializar o SDL"); 
        return 1;
    } 
    
    SDL_Window* window = SDL_CreateWindow(
        "Esfera",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        windowWidth,
        windowHeight,
        SDL_WINDOW_SHOWN
    );

    if (!window) {
        SDL_Log("Não foi possível criar a janela");
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        SDL_Log("Não foi possível criar o renderer");
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }




    Canvas canvas(windowWidth, windowHeight, windowDistance, numLines, numColumns);
    
    double radius = 400;
    double center[3] = { 0, 0, -(windowDistance + radius) };
    Sphere sphere(radius, center);
   
    int** display = canvas.Raycast(origin, sphere);

    bool isRunning = true;
    SDL_Event event;

    while (isRunning) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                isRunning = false;
            }
        }

        SDL_RenderClear(renderer);

        for (int i = 0; i < numLines; i++) {
            for (int j = 0; j < numColumns; j++) {
                if (display[i][j] == 0) {
                    SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
                    SDL_RenderDrawPoint(renderer, j, i); 
                }
                else {
                    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                    SDL_RenderDrawPoint(renderer, j, i); 
                }
            }
        }

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
} 