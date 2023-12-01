#include <iostream>
#include "SDL.h"

#define SDL_MAIN_HANDLED


int main(int argc, char* argv[])
{

    int windowWidth = 1280;
    int windowHeight = 720;


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

    bool isRunning = true;
    SDL_Event event;

    while (isRunning) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                isRunning = false;
            }
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();


    return 0;

};

