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
#define Bar_Offset 60

typedef struct button
{
    char *s;
    Rectangle Coord;
    Color col;
}button;

typedef struct bar
{
    Color col;
    Rectangle Coord;
} bar;

void Swap_Bars(Rectangle *a, Rectangle *b);
void Draw_Buttons(button *buttons, int sorting);
void Draw_Bars(bar *bars);
void Draw(button *buttons, int Array_exists,int sorting, bar *bars);
button* button_init();
button* Init();
bar* generate();
int StartBubbleSort(bar *bars, int Array_Exists, button *buttons);
int StartQuickSort(bar *bars, int Array_Exists, button *buttons,int pivot,int st);
int CheckAndDo_Button_Pressed(button *buttons, int *Array_Exists, bar **bars,int sorting);