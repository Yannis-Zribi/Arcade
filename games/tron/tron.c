#include <stdlib.h>
#include <stdio.h>

#include </opt/homebrew/Cellar/sdl2/2.26.1/include/SDL2/SDL.h> //MAC
#include </opt/homebrew/Cellar/sdl_ttf/2.0.11_2/include/SDL/SDL_ttf.h>

#include "../../func.h"
#include "tron.h"

#define WINNING_SCORE 3
#define CASE_SIZE 10
#define MAP_HEIGHT HEIGHT / CASE_SIZE
#define MAP_WIDTH WIDTH / CASE_SIZE





TronPlayer * createTronPlayer(int pn, int width, int height){
    TronPlayer * temp = malloc(sizeof(TronPlayer));

    if (pn == 1){
        temp->x = (width / 2) - 20;
        temp->y = height / 2;

        temp->dir_h = 1;
        temp->dir_v = 0;

        temp->score = 0;
    }else{
        temp->x = (width / 2) + 20;
        temp->y = height / 2;
        
        temp->dir_h = -1;
        temp->dir_v = 0;

        temp->score = 0;
    }
    
    return temp;
}

int ** createTronMap(int width, int height){
    int ** temp = malloc(sizeof(int *) * width);

    for (int i = 0; i < width; i++){
        temp[i] = malloc(sizeof(int) * height);

        //mise à 0 des cases
        for (int j = 0; j < height; j++){
            temp[i][j] = 0;
        }
    }

    return temp;
}

void viewMap(int ** map){
    printf("\n############## Dessin des trainées du joueur 1 ################\n");
    for (int i = 0; i < MAP_HEIGHT; i++){
        for (int j = 0; j < MAP_WIDTH; j++){
            if (map[i][j] == 1){
                printf("#");
            }else if (map[i][j] == 2){
                printf("@");
            }else{
                printf("O");
            }
        }
        printf("\n");
    }
}

void drawTron(SDL_Renderer * renderer, int ** map, TronPlayer * p1, TronPlayer * p2){

    //nettoyage de l'écran
    SDL_ClearScreen(renderer);

    
    


    //Rectangle
    SDL_Rect * rect = malloc(sizeof(SDL_Rect));
    


    //Dessin des trainées du joueur 1

    //changement de couleur
    if (SDL_SetRenderDrawColor(renderer, 153, 255, 255, SDL_ALPHA_OPAQUE) != 0){
        SDL_ExitWithError("Changement de couleur du rendu");
    }

    for (int i = 0; i < MAP_HEIGHT; i++){
        for (int j = 0; j < MAP_WIDTH; j++){
            if (map[i][j] == 1){
                rect->x = j * CASE_SIZE;
                rect->y = i * CASE_SIZE;
                rect->w = CASE_SIZE;
                rect->h = CASE_SIZE;

                SDL_RenderFillRect(renderer, rect);
            }
        }
    }
    


    //Dessin des trainées du joueur 2

    //changement de couleur
    if (SDL_SetRenderDrawColor(renderer, 255, 204, 153, SDL_ALPHA_OPAQUE) != 0){
        SDL_ExitWithError("Changement de couleur du rendu");
    }

    for (int i = 0; i < MAP_HEIGHT; i++){
        for (int j = 0; j < MAP_WIDTH; j++){
            if (map[i][j] == 2){
                rect->x = j * CASE_SIZE;
                rect->y = i * CASE_SIZE;
                rect->w = CASE_SIZE;
                rect->h = CASE_SIZE;
            
                SDL_RenderFillRect(renderer, rect);
            }
        }
    }


    //Dessin du joueur 1

    //changement de couleur
    if (SDL_SetRenderDrawColor(renderer, 0, 151, 255, SDL_ALPHA_OPAQUE) != 0){
        SDL_ExitWithError("Changement de couleur du rendu");
    }

    rect->x = p1->x * CASE_SIZE;
    rect->y = p1->y * CASE_SIZE;
    rect->w = CASE_SIZE;
    rect->h = CASE_SIZE;

    SDL_RenderFillRect(renderer, rect);


    //Dessin du joueur 2

    //changement de couleur
    if (SDL_SetRenderDrawColor(renderer, 255, 158, 0, SDL_ALPHA_OPAQUE) != 0){
        SDL_ExitWithError("Changement de couleur du rendu");
    }

    rect->x = p2->x * CASE_SIZE;
    rect->y = p2->y * CASE_SIZE;
    rect->w = CASE_SIZE;
    rect->h = CASE_SIZE;

    SDL_RenderFillRect(renderer, rect);



    //affichage de tous les éléments
    SDL_RenderPresent(renderer);
}



int updateTron(TronPlayer * p1, TronPlayer * p2, int ** map){

    int lose = 0;

    //Update de la map
    map[p1->y][p1->x] = 1;
    map[p1->y - p1->dir_v][p1->x - p1->dir_h] = 1;
    
    printf("\n\naprès changemnet 1 : \nX = %d | Y = %d\nX2 = %d | Y2 = %d\n\n", p1->x, p1->y, p1->x - p1->dir_h, p1->y - p1->dir_v);
    viewMap(map);

    map[p2->y][p2->x] = 2;
    map[p2->y - p2->dir_v][p2->x - p2->dir_h] = 2;

    printf("\n\naprès changemnet 2 : \n\n");
    viewMap(map);


    //Detection des touches
    SDL_Event event;

    while (SDL_PollEvent(&event)){
        if(event.type == SDL_QUIT){
            return -1;
        }
        if (event.type == SDL_KEYDOWN){
            switch (event.key.keysym.sym){
            //touches pour le joueur 1
            case SDLK_z:
                if (p1->dir_v != 1){
                    p1->dir_h = 0;
                    p1->dir_v = -1;
                }
                break;

            case SDLK_q:
                if (p1->dir_h != 1){
                    p1->dir_v = 0;
                    p1->dir_h = -1;
                }
                break;

            case SDLK_s:
                if (p1->dir_v != -1){
                    p1->dir_h = 0;
                    p1->dir_v = 1;
                }
                break;

            case SDLK_d:
                if (p1->dir_h != -1){
                    p1->dir_v = 0;
                    p1->dir_h = 1;
                }
                break;
            
            //touches pour le joueur 2
            case SDLK_UP:
                if (p2->dir_v != 1){
                    p2->dir_h = 0;
                    p2->dir_v = -1;
                }
                break;

            case SDLK_DOWN:
                if (p2->dir_v != -1){
                    p2->dir_h = 0;
                    p2->dir_v = 1;
                }
                break;

            case SDLK_LEFT:
                if (p2->dir_h != 1){
                    p2->dir_v = 0;
                    p2->dir_h = -1;
                }
                break;

            case SDLK_RIGHT:
                if (p2->dir_h != -1){
                    p2->dir_v = 0;
                    p2->dir_h = 1;
                }
                break;
            
            default:
                break;
            }
        }
    }

    
    //Update des positions
    //joueur 1
    p1->x = p1->x + (2 * p1->dir_h);
    p1->y = p1->y + (2 * p1->dir_v);


    if (map[p1->y][p1->x] != 0 || (p1->x > MAP_WIDTH || p1->x < 0) || (p1->y > MAP_HEIGHT || p1->y < 0)){
        p2->score = p2->score + 1;
        lose = 1;
    }

    

    //joueur 2
    p2->x = p2->x + (2 * p2->dir_h);
    p2->y = p2->y + (2 * p2->dir_v);

    if (map[p2->y][p2->x] != 0 || (p2->x > MAP_WIDTH || p2->x < 0) || (p2->y > MAP_HEIGHT || p2->y < 0)){
        p1->score = p1->score + 1;
        lose = 1;
    }
    

    //si un joueur à perdu
    if(lose){
        resetTronMap(p1, p2, map, MAP_WIDTH, MAP_HEIGHT);
    }


    //si un joueur atteint le score max
    if (p1->score == WINNING_SCORE){
        /* code */
    }else if (p2->score == WINNING_SCORE){
        /* code */
    }
    
    return 0;
}

void resetTronMap(TronPlayer * p1, TronPlayer * p2, int ** map, int width, int height){
    //Reset de la position du joueur 1
    p1->x = (width / 2) - 20;
    p1->y = height / 2;

    p1->dir_h = 1;
    p1->dir_v = 0;


    //Reset de la position du joueur 2
    p2->x = (width / 2) + 20;
    p2->y = height / 2;

    p2->dir_h = -1;
    p2->dir_v = 0;


    //Reset de la map
    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++){
            map[i][j] = 0;
        }
    }
}

void drawWinner(SDL_Renderer * renderer, int winner, int score_p1, int score_p2){
    //bloquer le jeu jusqu'au relancement de la part du joueur
}

void mainTronLoop(SDL_Window * window, SDL_Renderer * renderer){

    printf("tron launched");

    int ** map = NULL;
    map = createTronMap(MAP_WIDTH, MAP_HEIGHT);

    if (map == NULL){
        SDL_ExitWithError("allouage de la mémoire pour la map de tron");
    }

    

    TronPlayer * p1 = NULL;
    p1 = createTronPlayer(1, MAP_WIDTH, MAP_HEIGHT);

    if (p1 == NULL){
        SDL_ExitWithError("allouage de la mémoire pour le joueur 1 de tron");
    }
    
    TronPlayer * p2 = NULL;
    p2 = createTronPlayer(2, MAP_WIDTH, MAP_HEIGHT);

    if (p1 == NULL){
        SDL_ExitWithError("allouage de la mémoire pour le joueur 2 de tron");
    }


    int quitTron = 0;
    int update = 0;

    // testScreen(renderer);
    SDL_Event eventtron;

    while (!quitTron){
        update = updateTron(p1, p2, map);

        if (update == -1){
            quitTron = 1;
        }else if(update == 1){
            /* code */
        }else if(update == 2){
            /* code */
        }
        
        
        // else if (update == 1){
        //     drawWinner(renderer, 1, p1->score, p2->score);
        // }else if (update == 2){
        //     drawWinner(renderer, 2, p1->score, p2->score);
        // }

        drawTron(renderer, map, p1, p2);
        
        SDL_Delay(200);
    }
}