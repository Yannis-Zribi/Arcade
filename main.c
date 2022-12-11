#define SDL_MAIN_HANDLED
//MAC
//#include </opt/homebrew/Cellar/sdl2/2.26.1/include/SDL2/SDL.h> 
//Windows
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

#include "menu/menu.h"
#include "func.h"
#include "games/pong/pong.h"


/*
commande de compilation :
MAC : gcc main.c -o prog $(sdl2-config --cflags --libs)
WINDOWS : gcc main.c -o prog.exe -lmingw32 -lSDL2main -lSDL2 
WINDOWS sans terminal : gcc main.c -o prog.exe -I include -L lib -lmingw32 -lSDL2main -lSDL2 -mwindows
*/


int main(int argc, char **argv){

    //SDL_PrintVersion();

    //initialisation de SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0){
        SDL_ExitWithError("Initialisation SDL");;
    }
    
    //programme
    SDL_Window * window = NULL;
    SDL_Renderer * renderer = NULL;

    if(SDL_CreateWindowAndRenderer(800, 600, 0, &window, &renderer) != 0){
        SDL_ExitWithError("Impossible de créer la fenetre et le rendu");
    }
    SDL_SetWindowTitle(window,"JEUX");


        menu(window,renderer);     
    
 
  /*
  var gameplayed = 0;
  0=menu
  1=snake
  ...
  */


    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}
