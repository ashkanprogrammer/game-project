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
    return 0;
}