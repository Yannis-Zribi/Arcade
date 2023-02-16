#ifndef G
#define G

#define WIDTH_TABLE 10
#define HEIGTH_TABLE 20
#define CELL_SIZE 20

typedef struct Timer
{
    int initializedTimer;
}Timer;



Timer * createTimer();
void MainTetrisLoop(SDL_Renderer * renderer);
void PartialClean(SDL_Renderer * renderer);
int ** createArray(int height, int width);
void DrawControl(SDL_Renderer * renderer);
void DrawGame(SDL_Renderer * renderer,int ** miniArray,int ** permArray,int x,int y);
void DrawNext(SDL_Renderer * renderer,int ** miniArray);
void DrawScore(SDL_Renderer * renderer,int * score);
void supprLine(int row,int ** permArray);
int updateTetris(int ** permArray, int ** miniArray,int * x,int * y,int * score, SDL_Renderer * renderer,Timer * TIMESTAMP);
void copyArrayInto(int ** sourceArray,int ** destArray,int heigth, int width);
void updateMiniArray(int ** miniArray, int choice,int color);



#endif