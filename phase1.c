#include <stdio.h>
#include <math.h>
#include "raylib.h"

typedef struct{
    float x;
    float y;
}Vector;

typedef struct{
    Vector pos;
    Vector dir;
    Vector plane;
}Player;

int main(){
    InitWindow(1200, 900, "game window");
    Color cb1 = {0, 50, 250, 80};
    Color cr1 = {180, 0, 0, 255};
    Player player;
    player.pos.x = 600.0f;
    player.pos.y = 450.0f;
    player.dir.x = 1.0f;
    player.dir.y = 0.0f;
    player.plane.x = 0.0f;
    player.plane.y = 0.66f;
    SetTargetFPS(60);

    int map[15][15];
    for(int i = 0; i < 15; i++){
        for(int j = 0; j < 15; j++){
            if(i == 0 || i == 14 || j == 0 || j == 14)
                map[i][j] = 1;
            else map[i][j] = 0;
        }
    }
    return 0;
}