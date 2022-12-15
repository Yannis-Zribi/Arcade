//#include </opt/homebrew/Cellar/sdl2/2.26.1/include/SDL2/SDL.h> //MAC
#include <SDL2/SDL.h>  //Windows
#include <stdio.h>
#include <stdlib.h>
#include "func.h"

void SDL_ExitWithError(char * message){
    SDL_Log("ERREUR : %s > %s\n", message, SDL_GetError());
    SDL_Quit();
    exit(EXIT_FAILURE);
}

void SDL_PrintVersion(){
    SDL_version nb;
    SDL_VERSION(&nb);

    printf("SDL %d.%d.%d \n", nb.major, nb.minor, nb.patch);
}

void clean(SDL_Window * window){
    SDL_FillRect(SDL_GetWindowSurface(window),
    NULL,
    SDL_MapRGB(SDL_GetWindowSurface(window)->format,0,0,0));
}