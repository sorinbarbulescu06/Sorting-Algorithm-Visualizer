#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"
#include <string.h>

#define NB 3
#define Button_L 200
#define Button_H 50
#define Button_Offset 25
#define FPS 60
#define Width 1280
#define Height 720
#define Bar_Number 175
#define Bar_Width 5
typedef struct button
{
    char *s;
    Rectangle Coord;
    Color col;
}button;

void Draw_Buttons(button *buttons)
{
    int i;
    for(i = 0 ; i < NB; i++){
        DrawRectangleRec(buttons[i].Coord, buttons[i].col);
        DrawRectangleLinesEx(buttons[i].Coord, 3, BLACK);
        DrawText(buttons[i].s, buttons[i].Coord.x + Button_Offset / 2, buttons[i].Coord.y + 12, 20, BLACK);
    }
}

void Draw_Bars()
{
    
}

void Draw(button *buttons, int Array_exists)
{
    BeginDrawing();
    ClearBackground(DARKGRAY);
    Draw_Buttons(buttons);
    if(Array_exists == 1){
        Draw_Bars();
    }
    EndDrawing();
}
//initiem butoanele
button* button_init()
{
    button *buttons = malloc(NB*sizeof(button));
    if(buttons == NULL){
        exit(1);
    }
    int i, Blank_L;
    Blank_L = (Width - NB * Button_L) / (NB + 1);
    for(i = 0; i < NB; i++){
        buttons[i].Coord.x = (i + 1) * Blank_L + i * Button_L;
        buttons[i].Coord.y = Height - Button_Offset - Button_H;
        buttons[i].Coord.height = Button_H;
        buttons[i].Coord.width = Button_L;
        buttons[i].s = malloc(16 * sizeof(char));
        if(buttons[i].s == NULL)
            exit(1);
    }
    strcpy(buttons[0].s , "Randomise");
    strcpy(buttons[1].s , "Bubble Sort");
    strcpy(buttons[2].s , "Quick Sort");
    buttons[0].col = RED;
    buttons[1].col = YELLOW;
    buttons[2].col = BLUE;
    return buttons;
}

button* Init()
{
    InitWindow(Width, Height, "Sorting Alg. Visualizer");
    SetTargetFPS(FPS);
    button *buttons = button_init();
    return buttons;
}

int* generate()
{
    int i;
    int *v = malloc(Bar_Number * sizeof(int));
    for(i = 0; i < Bar_Number; i++){

    }
}

void CheckAndDo_Button_Pressed(button *buttons, int *Array_Exists, int *v)
{
    Vector2 Mouse_Pos = GetMousePosition();
    int i, ind = -1;
    bool Hover = false;
    for(i = 0; i < NB; i++){
        if(CheckCollisionPointRec(Mouse_Pos, buttons[i].Coord)){
            Hover = true;
            if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                ind = i;
            }
        }
    }
    if(Hover == true){
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
    }
    else
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    if(ind == 0){
        v =generate();
        *Array_Exists = 1;
    }
    if(ind == 1){
   //     StartBubbleSort();
    }
    if(ind == 2){
  //      StartQuickSort();
    }
}


int main()
{
    int i;
    int Button_Pressed = 0;
    int Array_Exists = 0;
    int *v;
    button *buttons;
    buttons = Init();
    while(!WindowShouldClose()){
        CheckAndDo_Button_Pressed(buttons, &Array_Exists, v);
        Draw(buttons, Array_Exists);
    }
    for(i = 0; i < NB; i++)
        free(buttons[i].s);
    free(buttons);
    CloseWindow();
    return 0;
}