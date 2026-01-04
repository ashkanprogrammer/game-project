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
    int u = 45, v = 195;
    const int TILE_SIZE = 54;
    for(int i = 0; i < 15; i++){
        for(int j = 0; j < 15; j++){
            if(i == 0 || i == 14 || j == 0 || j == 14)
                map[i][j] = 1;
            else map[i][j] = 0;
        }
    }

    while(!WindowShouldClose()){
        float dt = GetFrameTime();
        float base_move_speed = 150.0f;
        float base_rot_speed = 5.0f;
        float move_speed = base_move_speed * dt;
        float rot_speed = base_rot_speed * dt;

        if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            int a = GetMouseX();
            int b = GetMouseY();
            int px = (player.pos.x - v)/(TILE_SIZE);
            int py = (player.pos.y - u)/(TILE_SIZE);
            if(a >= 195 && a <= 1005 && b >= 45 && b <= 855){
                a = (a - v)/(TILE_SIZE);
                b = (b - u)/(TILE_SIZE);
                if(a != px || b != py) map[b][a] = 1;
            }
        }
        if(IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)){
            int a = GetMouseX();
            int b = GetMouseY();
            if(a >= 195 && a <= 1005 && b >= 45 && b <= 855){
                a = (a - v)/(TILE_SIZE);
                b = (b - u)/(TILE_SIZE);
                map[b][a] = 0;
            }
        }

        if(IsKeyDown(KEY_W)){
            float newx = player.pos.x + (player.dir.x * move_speed);
            float newy = player.pos.y + (player.dir.y * move_speed);
            int newa = (newx - v)/(TILE_SIZE);
            int newb = (newy - u)/(TILE_SIZE);
            int a = (player.pos.x - v)/(TILE_SIZE);
            int b = (player.pos.y - u)/(TILE_SIZE);
            if(map[b][newa] == 0)
                player.pos.x = newx;
            if(map[newb][a] == 0)
                player.pos.y = newy;
        }
        if(IsKeyDown(KEY_S)){
            float newx = player.pos.x - (player.dir.x * move_speed);
            float newy = player.pos.y - (player.dir.y * move_speed);
            int newa = (newx - v)/(TILE_SIZE);
            int newb = (newy - u)/(TILE_SIZE);
            int a = (player.pos.x - v)/(TILE_SIZE);
            int b = (player.pos.y - u)/(TILE_SIZE);
            if(map[b][newa] == 0)
                player.pos.x = newx;
            if(map[newb][a] == 0)
                player.pos.y = newy;
        }
        if(IsKeyDown(KEY_A)){
            float newx = player.pos.x + (player.dir.y * move_speed);
            float newy = player.pos.y - (player.dir.x * move_speed);
            int newa = (newx - v)/(TILE_SIZE);
            int newb = (newy - u)/(TILE_SIZE);
            int a = (player.pos.x - v)/(TILE_SIZE);
            int b = (player.pos.y - u)/(TILE_SIZE);
            if(map[b][newa] == 0)
                player.pos.x = newx;
            if(map[newb][a] == 0)
                player.pos.y = newy;
        }
        if(IsKeyDown(KEY_D)){
            float newx = player.pos.x - (player.dir.y * move_speed);
            float newy = player.pos.y + (player.dir.x * move_speed);
            int newa = (newx - v)/(TILE_SIZE);
            int newb = (newy - u)/(TILE_SIZE);
            int a = (player.pos.x - v)/(TILE_SIZE);
            int b = (player.pos.y - u)/(TILE_SIZE);
            if(map[b][newa] == 0)
                player.pos.x = newx;
            if(map[newb][a] == 0)
                player.pos.y = newy;
        }

        if(IsKeyDown(KEY_RIGHT)){
            float pdx = player.dir.x;
            float pdy = player.dir.y;
            float ppx = player.plane.x;
            float ppy = player.plane.y;
            player.dir.x = pdx * cos(rot_speed) - pdy * sin(rot_speed);
            player.dir.y = pdx * sin(rot_speed) + pdy * cos(rot_speed);
            player.plane.x = ppx * cos(rot_speed) - ppy * sin(rot_speed);
            player.plane.y = ppx * sin(rot_speed) + ppy * cos(rot_speed);
        }
        if(IsKeyDown(KEY_LEFT)){
            float pdx = player.dir.x;
            float pdy = player.dir.y;
            float ppx = player.plane.x;
            float ppy = player.plane.y;
            player.dir.x = pdx * cos(rot_speed) + pdy * sin(rot_speed);
            player.dir.y = pdy * cos(rot_speed) - pdx * sin(rot_speed);
            player.plane.x = ppx * cos(rot_speed) + ppy * sin(rot_speed);
            player.plane.y = ppy * cos(rot_speed) - ppx * sin(rot_speed);
        }
        
        BeginDrawing();
        ClearBackground(BLACK);
        for(int i = 0; i < 15; i++){
            for(int j = 0; j < 15; j++){
                if(map[j][i] == 0) DrawRectangle(v + i * TILE_SIZE, u + j * TILE_SIZE, TILE_SIZE, TILE_SIZE, WHITE);
                else DrawRectangle(v + i * TILE_SIZE, u + j * TILE_SIZE, TILE_SIZE, TILE_SIZE, cb1);
                DrawRectangleLines(v + i * TILE_SIZE, u + j * TILE_SIZE, TILE_SIZE, TILE_SIZE, DARKGRAY);
            }
        }
        float xe = 60.0f * player.dir.x;
        float ye = 60.0f * player.dir.y;
        DrawCircle(player.pos.x, player.pos.y, 18, cr1);
        DrawLine(player.pos.x, player.pos.y, player.pos.x + xe, player.pos.y + ye, cr1);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}