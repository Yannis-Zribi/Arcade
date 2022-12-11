#include </opt/homebrew/Cellar/sdl2/2.26.1/include/SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

#include "func.h"
#include "games/pong/pong.h"


/*
commande de compilation :
gcc main.c -o prog $(sdl2-config --cflags --libs)
*/


int main(int argc, char **argv){

    SDL_PrintVersion();

    //initialisation de SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0){
        SDL_ExitWithError("Initialisation SDL");
    }
    
    //programme
    SDL_Window * window = NULL;
    SDL_Renderer * renderer = NULL;

    if(SDL_CreateWindowAndRenderer(800, 600, 0, &window, &renderer) != 0){
        SDL_ExitWithError("Impossible de créer la fenetre et le rendu");
    }

        
    SDL_Event event;
    int quit = 0;
    while (!quit){
        while (SDL_PollEvent(&event)){
            if (event.type == SDL_QUIT){
                quit = 1;
            }
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}
