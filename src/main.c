#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"

int main()
{
    int Width = 800;
    int Height = 450;
    int FPS = 60;
    InitWindow(Width, Height, "Sorting Alg. Visualizer");
    SetTargetFPS(FPS);
    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(RAYWHITE);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}