#include <iostream>
#include <vector>
#include "Plane.hpp"
#include "CircularPlane.hpp"
#include "Canvas.hpp"
#include "Sphere.hpp"
#include "Ray.hpp"

    #define SDL_MAIN_HANDLED
    #include "SDL.h"


int main()
{
    std::vector<double> lightSource = {0, 5, 0};
    std::vector<double> intensity = {0.7, 0.7, 1.0};
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
    std::vector<double> center = { 0, 0, -(windowDistance + radius) };
    
    std::vector<double> normal = { 0, 0, 1 };
    

    double constAttenuation = 0.1;
    double linearAttenuation = 0.1;
    double quadraticAttenuation = 0.1;
    std::vector<double> ambientReflex(3, 0.5);
    std::vector<double> diffuseReflex(3, 0.5);
    std::vector<double> specularReflex(3, 0.5);
    int shininess = 3;
    
    //Sphere sphere(radius, center, ambientReflex, diffuseReflex, specularReflex, shininess);
    
    
    //Plane sphere(center, normal, ambientReflex, diffuseReflex, specularReflex, shininess);

    Sphere object(radius, center, constAttenuation, linearAttenuation,
                         quadraticAttenuation, ambientReflex, diffuseReflex, specularReflex, shininess);

    std::vector<std::vector<std::vector<double>>> display = canvas.Raycast(&object, lightSource, intensity);

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
   
                if (display[i][j][0] == -2) {
                    SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
                    SDL_RenderDrawPoint(renderer, j, i);
                }
                else {
                    SDL_SetRenderDrawColor(renderer, display[i][j][0] * 255, display[i][j][1] * 0, display[i][j][2] * 0, 255);
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

};

