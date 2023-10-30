#include <iostream>
#include "vec3Math.hpp"


//#define SDL_MAIN_HANDLED
//#include "SDL.h"



int main()
{      
 

 
 /*
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
*/    
}
