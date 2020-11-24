#include <SDL.h> 
#include <stdio.h>

#include "maze.h"
#include "app.c"

global b32 Global_Running;
global app_state Global_State = {0};

internal void HandleEvent(SDL_Event *event)
{
    switch (event->type)
    {
        case SDL_QUIT:
        {
            Global_Running = 0;
        } break;

        case SDL_KEYUP:
        {
            if (event->key.repeat == 0)
            {
                switch (event->key.keysym.scancode)
                {
                    case SDL_SCANCODE_SPACE:
                    {
                    } break;

                    case SDL_SCANCODE_ESCAPE:
                    {
                    } break;
                }
           }
        } break;

        case SDL_MOUSEBUTTONDOWN:
        {
        } break; 

        case SDL_MOUSEBUTTONUP: 
        {
        } break;

        case SDL_MOUSEMOTION: 
        {
        } break;
    }
}

int main(int argc, char** argv)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL_Init failed: %s", SDL_GetError());
    }

    SDL_Window *window = SDL_CreateWindow("Maze", 
                                          SDL_WINDOWPOS_UNDEFINED, 
                                          SDL_WINDOWPOS_UNDEFINED, 
                                          1281, 721, 0);

    if (window)
    {
        SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

        if (renderer)
        {
            Global_Running = 1;
            while (Global_Running)
            {
                SDL_Event event; 
                while (SDL_PollEvent(&event))
                {
                    HandleEvent(&event);
                }

                UpdateApp(renderer, &Global_State);
            }
        }
        else 
        {
            printf("SDL_CreateRenderer failed: %s", SDL_GetError());
        }
    }
    else
    {
        printf("SDL_CreateWindow failed: %s", SDL_GetError());
    }

    SDL_Quit();
    return 0; 
}