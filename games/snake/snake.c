
//--------- SDL ---------
//MAC
#include </opt/homebrew/Cellar/sdl2/2.26.1/include/SDL2/SDL.h> 
#include </opt/homebrew/Cellar/sdl_ttf/2.0.11_2/include/SDL/SDL_ttf.h>
 
//Windows
// #include <SDL2/SDL.h> 
// #include <SDL2/SDL_ttf.h>

//-----------------------

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "snake.h"
#include "../../func.h"
#include "../../menu/menu.h"



Snake * createSnake() {

    printf("\n\nCreation du serpent : \n");
    
    int midScreen = ((WIDTH / CASE_SIZE) % 2) ? (WIDTH / CASE_SIZE)/2 : ((WIDTH / CASE_SIZE) - 1)/2;
    printf("milieu de l'ecran : %d\n", midScreen);

    Snake * temp = NULL;


    for (int i = midScreen; i > midScreen - 3; i--){
        Snake * snake = malloc(sizeof(Snake));

        snake->y = 10;
        snake->x = i;
        snake->next = temp;
        temp = snake;

        printf("noeud nb %d : x = %d | y = %d | next = %p\n", i, snake->x, snake->y, snake->next);
        printf("temp = %p\n", temp);
    }
    return temp;
}

Snake * addSnakeNode(Snake * snake,int dir_h,int dir_v){
    printf("test test");
    Snake * newSnake = malloc(sizeof(Snake));
    newSnake->x = snake->x + dir_h;
    newSnake->y = snake->y + dir_v;
    newSnake->next=snake;
    
    return newSnake;
}

void createFruit(Fruit * fruit, Snake * snake){
    
    fruit->x = (rand() % MAX_CASE_WIDTH);
    fruit->y = (rand() % MAX_CASE_HEIGHT);
    //on empeche que le fruit soit a l'extrémité
    Snake * tempSnake = snake;

    int a = 1;

    while (a){
        if (fruit->x == tempSnake->x){
            if (fruit->y == tempSnake->y){
                fruit->x = rand() % MAX_CASE_WIDTH;
                fruit->y = rand() % MAX_CASE_HEIGHT;

                tempSnake = snake;
            }
        }

        tempSnake = tempSnake->next; 

        if(tempSnake->next != NULL){
            a = 0;
        }
    }
}

void viewAllNodes(Snake * snake){
    Snake * tempSnake = snake;
    int nextNodeNull = 0;
    int i = 1;
    printf("[HEAD]");

    while (!nextNodeNull){
        printf("snake node n°%d : x = %d | y = %d | next = %p\n", i, tempSnake->x, tempSnake->y, tempSnake->next);
        i++;

        if (tempSnake->next == NULL){
            nextNodeNull = 1;
        }

        tempSnake = tempSnake->next;
    }

    printf("\n");
    
}


void drawSnake(SDL_Renderer * renderer, Snake * snake, Fruit *fruit, int * score){

    Snake * tempSnake = snake;


    //nettoyage de l'écran
    SDL_ClearScreen(renderer);

    //changement de couleur
    if (SDL_SetRenderDrawColor(renderer, 200, 180, 180, SDL_ALPHA_OPAQUE) != 0){
        SDL_ExitWithError("Changement de couleur du rendu");
    }

    //Dessin du terrain
    SDL_Rect * rect = malloc(sizeof(SDL_Rect));

    //Dessin du snake
    int nextNodeNull = 0;

    while (!nextNodeNull){
        //printf("print snake node : x = %d | y = %d | next = %p\n", tempSnake->x, tempSnake->y, tempSnake->next);
        
        rect->x = tempSnake->x * CASE_SIZE;
        rect->y = tempSnake->y * CASE_SIZE;
        rect->h = CASE_SIZE;
        rect->w = CASE_SIZE;
        //printf("rect x= %d y=%d h=%d w=%d\n",rect->x,rect->y,rect->h,rect->w);
        SDL_RenderFillRect(renderer, rect);
        

        if (tempSnake->next == NULL){
            nextNodeNull = 1;
        }

        tempSnake = tempSnake->next;
        
    }
     viewAllNodes(snake);
    //changement de couleur
    if (SDL_SetRenderDrawColor(renderer, 200, 20, 20, SDL_ALPHA_OPAQUE) != 0){
        SDL_ExitWithError("Changement de couleur du rendu");
    }

    //Dessin fruit
    rect->x = fruit->x * CASE_SIZE;
    rect->y = fruit->y * CASE_SIZE;
    rect->h = CASE_SIZE;
    rect->w = CASE_SIZE;
    SDL_RenderFillRect(renderer, rect);

    free(rect);


    //Dessin du score
    // char buffer[12];
    // sprintf(buffer, "Score : %d", *score);

    // SDL_Color white = {180, 180, 200};

    // SDL_WriteText(renderer, 10, 10, 50, 20, white, buffer);

    //affichage de tous les éléments
    SDL_RenderPresent(renderer);
    printf("############\n");

}


void mainLoopSnake(SDL_Window* window, SDL_Renderer * renderer){

    Snake * snake = createSnake();

    Fruit * fruit = malloc(sizeof(Fruit));
    createFruit(fruit, snake);

    int dir_h = 1;
    //Directions horizontales:
    //  1 = droite
    // -1 = gauche
    //a initialisé à 1 au début toujours

    int dir_v = 0;
    //Directions horizontales:
    //  1 = bas
    // -1 = haut

    int score = 0;


    int quitsnake = 0;
    SDL_Event eventsnake;

    while(!quitsnake){
        if (updateSnake(renderer, snake, &snake, &score, fruit, &dir_h, &dir_v) == 0){
            printf("BREAKPOINT");

            //affichage du menu de game over
            if(gameOverMenuSnake(renderer, score) == 0){
                //free du serpent
                freeSnake(snake);

                //free du fruit
                free(fruit);

                //quitter le jeu snake
                quitsnake = 1;

                
            }else{
            //restart le jeu
                //on refait le snake entièrement pour repartir à zero
                freeSnake(snake);
                snake = createSnake();

                //reset des direction
                dir_h = 1;
                dir_v = 0;

                //reset du score
                score = 0;
            }


            //print lose menu

        };


        drawSnake(renderer, snake, fruit, &score);
        SDL_Delay(200);
    }
}

void freeSnake(Snake * snake){
    int nextNodeNull = 0;
    Snake * nextSnake = snake->next;
    Snake * nextNextSnake = nextSnake->next;

    free(snake);
    
    while(!nextNodeNull){
        free(nextSnake);

        nextSnake = nextNextSnake;
        nextNextSnake = nextSnake->next;

        if (nextNextSnake == NULL){
            free(nextSnake);
            nextNodeNull = 1;
        }
    }
}

int gameOverMenuSnake(SDL_Renderer * renderer, int score){
    int quit = 0;
    int choice = 0;
    SDL_Event event;
    SDL_Rect * rect = malloc(sizeof(SDL_Rect));

    while (!quit){
    //Dessin du menu
        //clear de la fenetre
        SDL_ClearScreen(renderer);

        //changement de couleur du renderer
        if (SDL_SetRenderDrawColor(renderer, 255, 0,0, SDL_ALPHA_OPAQUE) != 0){
            SDL_ExitWithError("Changement de couleur du rendu");
        }

        //
        rect->w = 80;
        rect->h = 60;
        rect->x = 300;

        for (int i = 0; i < 2; i++){
            //on change la couleur du rectangle correspondant au choix du user
            if (choice == i){
                if (SDL_SetRenderDrawColor(renderer, 0, 255,0, SDL_ALPHA_OPAQUE) != 0){
                    SDL_ExitWithError("Changement de couleur du rendu");
                }
            }
            
            //calcul du y du rectangle
            rect->y = 140 + (80 + (rect->h * i * 2));

            //rendu du rectangle
            SDL_RenderFillRect(renderer, rect);

            //reset de la couleur
            if (SDL_SetRenderDrawColor(renderer, 255, 0,0, SDL_ALPHA_OPAQUE) != 0){
                SDL_ExitWithError("Changement de couleur du rendu");
            }
        }

        //deuxieme rectangle
        rect->w = 240;
        rect->h = 80;
        rect->x = WIDTH/2-rect->w/2;
        rect->y = 100;

        //rendu du rectangle
        SDL_RenderFillRect(renderer, rect);

        //recentrer les zones   
        SDL_Color greyWhite = {200, 200, 200};
        char * dico[] = {"voulez vous rejouer ?","oui","non"};

        // SDL_WriteTextBuffered(renderer,30,30,150,30,greyWhite,dico[0]);
        // SDL_WriteTextBuffered(renderer,60,60,60,60,greyWhite,dico[1]);
        // SDL_WriteTextBuffered(renderer,90,90,90,90,greyWhite,dico[2]);

        SDL_RenderPresent(renderer);


        //gestion des choix du user
        while (SDL_PollEvent(&event)){
            switch (event.type){

                case SDL_QUIT:
                    return 0;
                    break; 

                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym){

                        case SDLK_DOWN:
                            if (choice < 1){
                                choice++;
                                printf("choice : %d",choice);
                            }
                            break;

                        case SDLK_UP:
                            if (choice > 0){
                                choice--;
                                printf("choice : %d",choice);
                            }
                            break;

                        case SDLK_RETURN:
                            return choice;
                            break;
                    }
                    break;
            }
        }
    }
    return 0;
}

int updateSnake(SDL_Renderer * renderer, Snake * snake, Snake ** snake_pointer, int * score, Fruit * fruit, int * dir_h, int * dir_v){

    //vérification des entrées du user
    SDL_Event event;

    while (SDL_PollEvent(&event)){
        if (event.type == SDL_QUIT){
            //quitter le programme
            return 0;
        }
        if (event.type == SDL_KEYDOWN){
                //nécessite un cooldown entre les touches
            switch (event.key.keysym.sym){

                case SDLK_ESCAPE:
                        if(Escape(renderer) == 0){
                            return 0;
                        }
                    break;

                case SDLK_UP:
                    if(*dir_v != 1){
                        printf("UP\n");
                        *dir_v = -1;
                        *dir_h = 0;
                    }
                    break;

                case SDLK_DOWN:
                    if(*dir_v != -1){
                        printf("DOWN\n");
                        *dir_v = 1;
                        *dir_h = 0;
                    }
                    break;

                case SDLK_LEFT:
                    if(*dir_h != 1){
                        printf("LEFT\n");
                        *dir_h = -1;
                        *dir_v = 0;
                    }
                    break;

                case SDLK_RIGHT:
                    if(*dir_h != -1){
                        printf("RIGHT\n");
                        *dir_h = 1;
                        *dir_v = 0;
                    }
                    break;
                
                default:
                    break;
            }
        }
    }
    //Update de la position du snake en fonction de sa direction
    
    int tempX, tempX2;
    int tempY, tempY2;
    int nextNodeNull = 0;
    int firstLoop = 1;
    Snake * tempSnake = snake;

    while (!nextNodeNull){

        if (firstLoop){
            tempX = tempSnake->x;
            tempY = tempSnake->y;

            tempSnake->x = tempSnake->x + *dir_h;
            tempSnake->y = tempSnake->y + *dir_v;

            //vérification de collisions avec les côtés de la fenetre
            if ((snake->x < 0 || snake->x > MAX_CASE_WIDTH) || (snake->y < 0 || snake->y > MAX_CASE_HEIGHT)){
                printf("loose\n");
                return 0;
            }

            //vérification si le serpent s'est mangé lui-même
            if (*score > 0){
                int nextNodeNull = 0;
                Snake * verifSnake = tempSnake->next;

                while (!nextNodeNull){
                    if (tempSnake->x == verifSnake->x){
                        if (tempSnake->y == verifSnake->y){
                            printf("loose\n");
                            return 0;
                        }
                    }
                    

                    if (verifSnake->next == NULL){
                        nextNodeNull = 1;
                    }

                    verifSnake = verifSnake->next;
                
                }
            }
            

            
            

            firstLoop = 0;

        }else{
            tempX2 = tempSnake->x;
            tempY2 = tempSnake->y;

            tempSnake->x = tempX;
            tempSnake->y = tempY;

            tempX = tempX2;
            tempY = tempY2;

        }
        

        if (tempSnake->next == NULL){
            nextNodeNull = 1;
        }
        
        tempSnake = tempSnake->next;
    }
    
    


    //si il a mangé un fruit, augmenter sa taille et faire spawn un nouveau fruit
    if (snake->x == fruit->x && snake->y == fruit->y){
        //ajout d'un noeud au snake
        *snake_pointer = addSnakeNode(snake,*dir_h,*dir_v);

        //création d'un nouveau fruit
        createFruit(fruit,snake);

        //incrémentation du score
        *score = *score + 1;
    }
    
    return 1;
}






















































// void insertBeginning(Snake* snake, int x, int y) {
    
//     if (snake->head == NULL) {
        
//         Node* node = malloc(sizeof(Node));
//         if (node != NULL) {
//             node->next = snake->tail;
//             node->body.x = x;
//             node->body.y = y;
//             node->body.w = 25;
//             node->body.h = 25;
//             snake->head = node;
//         }
//         return;
//     }

//     else {
//         Node* temp = snake->head;
//         Node* node = malloc(sizeof(Node));
//         if (node != NULL) {
//             node->body.x = x;
//             node->body.y = y;
//             node->body.w = 25;
//             node->body.h = 25;
//             node->next = snake->head;
//             snake->head = node;
//         }
        
//     }
    
// }

// void insertEnd(Snake* snake, int x, int y) {

//     if (snake->tail == NULL) {
//         Node* node = malloc(sizeof(Node));
//         node->next = NULL;
//         snake->head->next = node;
//         node->body.x = x;
//         node->body.y = y;
//         node->body.w = 25;
//         node->body.h = 25;
//         snake->tail = node;
//     }

//     else {
//         Node* node = malloc(sizeof(Node));
//         if (node != NULL) {
//             node->next = NULL;
//             node->body.x = x;
//             node->body.y = y;
//             node->body.w = 25;
//             node->body.h = 25;
//             snake->tail->next = node;
//             snake->tail = node;
//         }
        
//     }
// }

// void deleteBeginning(Snake* snake) {
    
//     if (snake->head != NULL) {
//         Node* temp = snake->head;
//         snake->head = snake->head->next;
//         free(temp);
//     }
// }

// void deleteEnd(Snake* snake) {

//     if (snake->tail != NULL) {
//         Node* temp = snake->head;
//         while (temp->next != snake->tail) {
//             temp = temp->next;
//         }
//         snake->tail = temp;
//         free(temp);
//     }

// }