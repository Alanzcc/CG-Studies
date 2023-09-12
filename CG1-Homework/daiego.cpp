#include <iostream>
#include <Eigen>
#include <SDL.h>

// https://lazyfoo.net/tutorials/SDL/01_hello_SDL/windows/msvc2019/index.php

class Ray
{
public:
    Eigen::Vector3d initialPoint;
    Eigen::Vector3d direction;

    Ray(Eigen::Vector3d initialPoint, Eigen::Vector3d direction)
    {
        this->initialPoint = initialPoint;
        this->direction = direction.normalized();
    }
};

class Sphere
{
public:
    double radius;
    Eigen::Vector3d center;

    Sphere(double radius, Eigen::Vector3d center)
    {
        this->radius = radius;
        this->center = center;
    }

    bool hasInterceptedRay(Ray ray)
    {
        Eigen::Vector3d w = ray.initialPoint - this->center;
        double bHat = w.dot(ray.direction);
        double c = w.dot(w) - this->radius * this->radius;

        return (bHat * bHat - c >= 0);
    }
};

class Canvas
{
public:
    int windowDistance;
    int windowWidth;
    int windowHeight;
    int numLines;
    int numColumns;
    int deltaX;
    int deltaY;
    int jXMin;
    int jYMax;

    Canvas(int windowDistance, int windowWidth, int windowHeight, int numLines, int numColumns)
    {
        this->windowDistance = windowDistance;
        this->windowWidth = windowWidth;
        this->windowHeight = windowHeight;
        this->numLines = numLines;
        this->numColumns = numColumns;

        this->deltaX = windowWidth / numColumns;
        this->deltaY = windowHeight / numLines;

        this->jXMin = -(windowWidth / 2);
        this->jYMax = windowHeight / 2;
    }

    Eigen::ArrayXXf raycast(Eigen::Vector3d observable, Sphere sphere)
    {
        Eigen::ArrayXXf canvas = Eigen::ArrayXXf::Zero(this->numLines, this->numColumns);
        int yL, xC, intercepted;
        Eigen::Vector3d pJ;

        for (int l = 0; l < this->numLines; l++)
        {
            yL = this->jYMax - l * this->deltaY - this->deltaY / 2;

            for (int c = 0; c < this->numColumns; c++)
            {
                xC = this->jXMin + c * this->deltaX + this->deltaX / 2;

                pJ << xC, yL, -(this->windowDistance);

                Ray ray(observable, pJ);

                intercepted = sphere.hasInterceptedRay(ray);
                if (intercepted)
                    canvas(l, c) = 1;
            }
        }

        return canvas;
    }
};

int main(int argc, char *argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        SDL_Log("Não foi possível inicializar o SDL");
        return 1;
    }

    Eigen::Vector3d origin(0, 0, 0);

    int windowDistance = 300;
    int windowWidth = 1280;
    int windowHeight = 720;
    int numColumns = 1280;
    int numLines = 720;

    SDL_Window *window = SDL_CreateWindow(
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

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer)
    {
        SDL_Log("Não foi possível criar o renderer");
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    Canvas canvas(windowDistance, windowWidth, windowHeight, numLines, numColumns);

    double sphereRadius = 400;
    Eigen::Vector3d sphereCenter(0, 0, -(windowDistance + sphereRadius));
    Sphere sphere(sphereRadius, sphereCenter);

    Eigen::ArrayXXf display = canvas.raycast(origin, sphere);

    bool isRunning = true;
    SDL_Event event;

    while (isRunning)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                isRunning = false;
            }
        }

        SDL_RenderClear(renderer);

        for (int i = 0; i < numLines; i++)
        {
            for (int j = 0; j < numColumns; j++)
            {
                if (display(i, j) == 0)
                {
                    SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
                    SDL_RenderDrawPoint(renderer, j, i);
                }
                else
                {
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
    return 0;
}