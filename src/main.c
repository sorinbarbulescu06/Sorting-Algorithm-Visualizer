#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"
#include <string.h>
#define NB 4
#define Button_L 200
#define Button_H 50
#define Button_Offset 25

typedef struct button
{
    char *s;
    int xb;
}button;

void Draw_Buttons(button *buttons, int H)
{
    Color culoare[] = { BLUE, YELLOW, RED, GREEN};
    int i;
    for(i = 0 ; i < NB; i++){
        DrawRectangle(buttons[i].xb, H - Button_Offset - Button_H , Button_L, Button_H, culoare[NB - 1 - i]);
    }
}

void Draw(button *buttons,int H)
{
    BeginDrawing();
    ClearBackground(DARKGRAY);
    Draw_Buttons(buttons, H);
    EndDrawing();
}
//initiem butoanele
button* button_init(int W)
{
    button *buttons = malloc(NB*sizeof(button));
    if(buttons == NULL){
        exit(1);
    }
    int i, Blank_L;
    Blank_L = (W - NB * Button_L) / (NB + 1);
    for(i = 0; i < NB; i++){
        buttons[i].xb = (i + 1) * Blank_L + i * Button_L;
        buttons[i].s = malloc(16 * sizeof(char));
        if(buttons[i].s == NULL)
            exit(1);
    }
    //randomise button
    strcpy(buttons[0].s , "Randomise");
    strcpy(buttons[1].s , "Bubble Sort");
    strcpy(buttons[2].s , "Quick Sort");
    return buttons;
}

button* Init(int Width, int Height, int FPS)
{
    InitWindow(Width, Height, "Sorting Alg. Visualizer");
    SetTargetFPS(FPS);
    BeginDrawing();
    ClearBackground(WHITE);
    EndDrawing();
    button *buttons = button_init(Width);
    return buttons;
}

int main()
{
    int Width = 1280;
    int Height = 720;
    int FPS = 60;
    button *buttons;
    buttons = Init(Width, Height, FPS);
    while(!WindowShouldClose()){
        Draw(buttons, Height);
    }
    CloseWindow();
    return 0;
}