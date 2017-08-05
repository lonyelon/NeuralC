#include <iostream>
#include <vector>
#include <string>
#include <SDL.h>
#include "Neuron.h"

#define e 2.718281828459045
#define pi 3.141592653589793238462

using namespace std;



int main(int argc, char** args)
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* w = SDL_CreateWindow("NeuralNet", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, SDL_WINDOW_SHOWN);
    SDL_Renderer* r = SDL_CreateRenderer(w, -1, SDL_RENDERER_ACCELERATED);

    SDL_Rect r0 = { 100, 100, 100, 100 };

    SDL_Event ev;
    bool running = true;
    while (running) 
    {
        while (SDL_PollEvent(&ev) != 0) 
        {
            if (ev.type == SDL_QUIT) 
            {
                running = false;
            }

            float speed = 1;
        }

        SDL_SetRenderDrawColor(r, 21, 21, 21, 255);
        SDL_RenderClear(r);
        SDL_SetRenderDrawColor(r, 255, 255, 21, 255);
        SDL_RenderDrawRect(r, &r0);
        SDL_RenderPresent(r);
        SDL_UpdateWindowSurface(w);
        SDL_Delay(1000/60);
    }

    SDL_DestroyWindow(w);
    SDL_Quit();

    return 0;
}